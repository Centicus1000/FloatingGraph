#ifndef FloatGraph_hpp
#define FloatGraph_hpp

#include "imgui/imgui.h"
#include "imgui/implot.h"

#include "vml/vec2.h"
#include "vml/graph.h"



struct Node
{
    vml::vec2 pos;
    vml::vec2 speed{ 0.f, 0.f };
    vml::vec2 accel{ 0.f, 0.f };
    
    Node();
    Node(const Node&);
    
    ImVec2 coords() const;
};

class FloatGraph : public vml::Graph< Node* >
{
public:
    // attributes
    float g_fr{ .4f }; // factor for friction
    float g_rm{ 1.f }; // factor for random movement
    float g_hs{ .1f }; // factor for home sickness
    float g_ps{ .3f }; // factor for personal space
    float g_es{ .2f }; // factor for edge stiffness
    float g_ea{ .3f }; // factor for edge alignment

    float movement{ 0.f };
    
    FloatGraph();
    ~FloatGraph();
    
    void plot() const;
    void new_random_node();
    void new_random_edge();
    void update(float);
    
};

#endif /* FloatGraph_hpp */
