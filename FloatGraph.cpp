#include "FloatGraph.hpp"

#include <random>

static vml::vec2 random_vec2()
{
    static std::random_device rd{};
    static std::mt19937 gen{rd()};
    static std::normal_distribution<float> d{ 0.f, 2.f*vml::pi };
    return vml::polar(d(gen));
}

// ----------------------------------------------

Node::Node() : pos(0.f, 0.f)
{}

Node::Node(const Node& other) : pos(other.pos)
{
    pos += random_vec2();
}

ImVec2 Node::coords() const
{
    return ImPlot::PlotToPixels(ImVec2(pos.x, pos.y));
}
// ----------------------------------------------
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
        ImPlot::GetPlotDrawList() -> AddCircleFilled(c, 10.f, IM_COL32(105, 73, 110, 255));
        ImPlot::Annotation(n.pos.x,n.pos.y,ImVec4(0,0,0,0),ImVec2(0,0),false,"%s", std::to_string(k).c_str());
    }
}

void FloatGraph::insert_random()
{
    
    Node* n{ (nodes.size()==0) ? new Node() : new Node(*nodes.back()) };
    nodes.emplace_back( n );
    
    size_t s{ nodes.size() };
    
    if (s > 1)
    {
        std::random_device rd;  //Will be used to obtain a seed for the random number engine
        std::mt19937 gen{ rd() }; //Standard mersenne_twister_engine seeded with rd()
        std::uniform_int_distribution<Key> distrib(0, s-2);
        
        Key parent{ distrib(gen) };
        link(parent, s-1);
    }
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
        
        // Origin Suction
        x.accel += g_os * -x.pos;
        
        // Friction Damping
        x.accel += g_fd * -x.speed;
        
        // Random Noise
        x.accel += g_rn * random_vec2();
        
        for (Key j{ i+1 }; j<nodes.size(); j++)
        {
            Node& y{ *nodes[j] };

            vml::vec2 d{ x.pos - y.pos };
            float n{ d.norm() };
            vml::vec2 a{ d / (n*n*n) };
            x.accel += g_nr * a;
            y.accel -= g_nr * a;
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

