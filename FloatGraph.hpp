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
    float g_os{ .1f }; // factor for origin suction
    float g_fd{ .4f }; // factor for friction damping
    float g_nr{ .2f }; // factor for node repelling
    float g_es{ .4f }; // factor for edge stiffnes
    float g_rn{ .1f }; // factor for random noise
    float g_ea{ .1f }; // factor for edge alignment

    float movement{ 0.f };
    
    ~FloatGraph();
    
    void plot() const;
    void insert_random();
    void update(float);
    
};

#endif /* FloatGraph_hpp */
