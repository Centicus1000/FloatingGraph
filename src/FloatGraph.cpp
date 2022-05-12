#include "FloatGraph.hpp"

#include <random>

static std::random_device rd;
static std::mt19937 gen{ rd() };

static vml::vec2 random_vec2()
{
    static std::normal_distribution<float> d{ 0.f, 2.f*vml::pi };
    return vml::polar(d(gen));
}

template<typename T>
static T randi(T max)
{
    std::uniform_int_distribution<T> distrib(0, max);
    return distrib(gen);
}

// ----------------------------------------------

Node::Node() : pos( random_vec2() )
{}

Node::Node(const Node& other) : pos(other.pos)
{
    pos += .3f * random_vec2();
}

ImVec2 Node::coords() const
{
    return ImPlot::PlotToPixels(ImVec2(pos.x, pos.y));
}


// ----------------------------------------------
FloatGraph::FloatGraph()
{
    // insert first node at init
    new_random_node();
}


FloatGraph::~FloatGraph()
{
    for (Node* n : nodes) delete n;
}


void FloatGraph::plot() const
{
    // edge lambda
    std::function<void(const Edge&)> draw_edge
    {
        [this] (const Edge& e)
        {
            const Node& p{ *nodes[e.parent] };
            const Node& c{ *nodes[e.child]  };
            ImPlot::GetPlotDrawList() -> AddLine(p.coords(), c.coords(), IM_COL32(105, 73, 110, 255));
        }
    };
    for_edges(draw_edge);
    
    // node lambda
    for (Key k{ 0 }; k<nodes.size(); k++)
    {
        const Node& n{ *nodes[k] };
        auto c{ n.coords() };
        ImU32 col{ ImPlot::SampleColormapU32(.5f*n.speed.norm(), ImPlotColormap_Plasma) };
        ImPlot::GetPlotDrawList() -> AddCircleFilled(c, 10.f, col);
        ImPlot::Annotation(n.pos.x,n.pos.y,ImVec4(0,0,0,0),ImVec2(0,0),false,"%s", std::to_string(k).c_str());
    }
}

void FloatGraph::new_random_node()
{
    Key s{ nodes.size() };
    if (s >= 1)
    {
        Key parent{ randi(s-1) };
        
        // insert new node close to parent
        Node* n{ new Node(*nodes[parent]) };
        nodes.emplace_back( n );
        
        // link parent and child
        // s is now index of new node
        link(parent, s);
    }

    else
    {
        // insert first node
        Node* n{ new Node() };
        nodes.emplace_back( n );
    }
}

void FloatGraph::new_random_edge()
{
    Key max{ nodes.size()-1};
    Key parent{ randi(max) };
    Key child{ randi(max) };
    while (child==parent && is_edge(parent, child)) child = randi(max);
    link(parent, child);
}

inline float sq(float x) {return x*x;}

void FloatGraph::update(float dt)
{
    movement = 0;
    
    // update pysics
    for (Node* nptr : nodes)
    {
        Node& n{ *nptr };
        
        n.pos += dt * n.speed;
        n.speed += dt * n.accel;
        n.accel = vml::vec2(0);
        movement +=  sq(n.speed.x) + sq(n.speed.y);
    }
    
    // iterrate nodes and set new accel
    for (Key i{ 0 }; i<nodes.size(); i++)
    {
        Node& x{ *nodes[i] };
        
        // Friction
        x.accel += g_fr * -x.speed;
        
        // Random Movement
        x.accel += g_rm * random_vec2();
        
        // Home Sickness
        x.accel += g_hs * -x.pos;
        
        // Personal Space
        for (Key j{ i+1 }; j<nodes.size(); j++)
        {
            Node& y{ *nodes[j] };

            vml::vec2 d{ x.pos - y.pos };
            float n{ d.norm() };
            vml::vec2 a{ d / (n*n*n) };
            x.accel += g_ps * a;
            y.accel -= g_ps * a;
        }
        
    }
    
    // edge lambda
    std::function<void(Edge&)> upt_edge
    {
        [this] (Edge& e)
        {
            Node& a{ *nodes[e.parent] };
            Node& b{ *nodes[e.child ] };
            
            // Edge Stiffness
            vml::vec2 d{ b.pos - a.pos };
            vml::vec2 f{ (d.norm() - 1.f) * d.unit() };
            a.accel += g_es * f;
            b.accel -= g_es * f;
            
            // Edge Alignment
            float l{ 1.f - d.x };
            a.accel.x -= g_ea * l;
            b.accel.x += g_ea * l;
        }
    };
    for_edges(upt_edge);
}

