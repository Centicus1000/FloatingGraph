#define IMGUI_DISABLE_OBSOLETE_FUNCTIONS 1
#include "imgui/imgui.h"
#include "imgui/implot.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "glad/gl.h"
#include "GLFW/glfw3.h"

#include "vml/vec2.h"

#include "timer.h"

#include "FloatGraph.hpp"

#include <iostream>

// title
const char* title { "Flaoting Graph" };

// instances
vml::vec2 screen { 1190, 740 };
GLFWwindow*         window      { nullptr };

// glfw callbacks forward declarations
static void _error_callback (int error, const char* description);
static void _key_callback   (GLFWwindow* window, int key, int scancode, int action, int mods);
static void _scroll_callback(GLFWwindow* window, double dx, double dy);
static void _mouse_callback (GLFWwindow* window, double xd, double yd);
static void _click_callback (GLFWwindow* window, int button, int action, int mods);
static void _char_callback  (GLFWwindow* window, unsigned int c);
static void _resize_callback(GLFWwindow* window, int width, int height);

// utility structure for realtime plot
struct ScrollingBuffer {
    int MaxSize;
    int Offset;
    ImVector<ImVec2> Data;
    ScrollingBuffer(int max_size = 2000) {
        MaxSize = max_size;
        Offset  = 0;
        Data.reserve(MaxSize);
    }
    void AddPoint(float x, float y) {
        if (Data.size() < MaxSize)
            Data.push_back(ImVec2(x,y));
        else {
            Data[Offset] = ImVec2(x,y);
            Offset =  (Offset + 1) % MaxSize;
        }
    }
    void Erase() {
        if (Data.size() > 0) {
            Data.shrink(0);
            Offset  = 0;
        }
    }
};

int main(int argc, char const *argv[])
{
    // set up glfw window
    glfwSetErrorCallback(_error_callback);
    if (glfwInit() == 0) {
        std::cerr << "GLFW Error: failed to initialize" << std::endl;
        return -1;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    
    // create glfw window
    window = glfwCreateWindow((int)screen.x, (int)screen.y, title, /*glfwGetPrimaryMonitor()*/NULL, NULL);
    if (window == nullptr) {
        std::cerr << "GLFW Error: failed to create window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    int version = gladLoadGL(glfwGetProcAddress);
    std::cout << "GL " << GLAD_VERSION_MAJOR(version) << "." << GLAD_VERSION_MINOR(version) << "\n"
    << "OpenGL " << glGetString(GL_VERSION) << ", GLSL " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
    
    // set up callbacks
    glfwSetKeyCallback(window, _key_callback);
    glfwSetScrollCallback(window, _scroll_callback);
    glfwSetCharCallback(window, _char_callback);
    glfwSetMouseButtonCallback(window, _click_callback);
    glfwSetCursorPosCallback(window, _mouse_callback);
    glfwSetWindowSizeCallback(window, _resize_callback);
    
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImPlot::CreateContext();
    if (!ImGui_ImplGlfw_InitForOpenGL(window, false)) {
        printf("ImGui Error: ImGui_ImplGlfw_InitForOpenGL failed\n");
        assert(false);
    }
#if __APPLE__
    const char* glslVersion{ "#version 150" };
#else
    const char* glslVersion{ NULL };
#endif
    if (!ImGui_ImplOpenGL3_Init(glslVersion)) {
        printf("ImGui Error: ImGui_ImplOpenGL3_Init failed\n");
        assert(false);
    }
    
    // background color: white
    glClearColor(1.f, 1.f, 1.f, 1.0f);
    
    
    // render loop
    Timer timer; float time;
    FloatGraph fg;
    while (!glfwWindowShouldClose(window)) {
        time += timer.dt();
        timer.tik();
        
        // update viewport
        int bufferWidth, bufferHeight;
        glfwGetFramebufferSize(window, &bufferWidth, &bufferHeight);
        glViewport(0, 0, bufferWidth, bufferHeight);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        // gui commands
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        
        // ----------------------------------------------
        
//        ImPlot::ShowDemoWindow();
        ImGui::SetNextWindowPos(ImVec2(0,0), ImGuiCond_Always);
        ImGui::SetNextWindowSize(ImVec2(screen.x, screen.y), ImGuiCond_Always);
        ImGui::Begin("- no title -",nullptr, ImGuiWindowFlags_NoResize|ImGuiWindowFlags_NoTitleBar);
        ImGui::BeginChild("Left Child", ImVec2(screen.x * 0.666f, -1));
        if (ImPlot::BeginPlot("Some Graph",ImVec2(-1,-1)))
        {
            ImPlot::SetupAxesLimits(-5., +5., -5., +5.);
            ImPlot::PushPlotClipRect();

            fg.plot();
            ImPlot::PopPlotClipRect();
            ImPlot::EndPlot();
        }
        ImGui::EndChild();

        ImGui::SameLine();
        ImGui::BeginChild("Right Child", ImVec2(0, -1));
        if (ImGui::Button("Add Node")) fg.insert_random();
        ImGui::SameLine();
        ImGui::Text("#nodes = %lu", fg.nodes.size());
        ImGui::Separator();
        ImGui::DragFloat("Friction Damping", &fg.g_fr, 0.001f);
        ImGui::DragFloat("Random Movement", &fg.g_rm, 0.001f);
        ImGui::DragFloat("Home Sickness", &fg.g_hs, 0.001f);
        ImGui::DragFloat("Personal Space", &fg.g_ps, 0.001f);
        ImGui::DragFloat("Edge Stiffness", &fg.g_es, 0.001f);
        ImGui::DragFloat("Edge Alignment", &fg.g_ea, 0.001f);
        ImGui::Separator();
        
        if (ImPlot::BeginPlot("Movement",ImVec2(-1, 150)))
        {
            static ScrollingBuffer sdata( 1000 );
            sdata.AddPoint(time, fg.movement);
            ImPlot::SetupAxisLimits(ImAxis_X1,time - sdata.Data.size() * timer.target.count(), time, ImGuiCond_Always);
            ImPlot::SetupAxisLimits(ImAxis_Y1,0,6,ImGuiCond_Always);
            ImPlot::SetNextFillStyle(IMPLOT_AUTO_COL,0.5f);
            ImPlot::PlotShaded("", &sdata.Data[0].x, &sdata.Data[0].y, sdata.Data.size(), -INFINITY, sdata.Offset, 2 * sizeof(float));
            ImPlot::EndPlot();

        }
        
        ImGui::EndChild();

        ImGui::End();
        
        fg.update(timer.dt());
        
        // ----------------------------------------------
        
        // finish up frame
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        glfwSwapBuffers(window);
        glfwPollEvents();
        timer.tok();
    }
    
    // clean up
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImPlot::DestroyContext();
    ImGui::DestroyContext();
    glfwTerminate();
    
    return 0;
}


// callbacks
void _error_callback(int error, const char* description)
{
    std::cerr << "GLFW Error: \n\tcode: " << error << "\n\tdesc: " << description;
}
void _key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    ImGui_ImplGlfw_KeyCallback(window, key, scancode, action, mods);
    if (ImGui::GetIO().WantCaptureKeyboard) return;
    
    // check keys
    if (action == GLFW_PRESS) {
        switch (key) {
                // quit
            case GLFW_KEY_ESCAPE:
                glfwSetWindowShouldClose(window, GL_TRUE);
                break;
        }
    }
}
void _char_callback(GLFWwindow* window, unsigned int c)
{
    ImGui_ImplGlfw_CharCallback(window, c);
}
void _click_callback(GLFWwindow* window, int button, int action, int mods)
{
    ImGui_ImplGlfw_MouseButtonCallback(window, button, action, mods);
}
void _mouse_callback(GLFWwindow* window, double xd, double yd)
{}
void _scroll_callback(GLFWwindow* window, double dx, double dy)
{
    ImGui_ImplGlfw_ScrollCallback(window, dx, dy);
    if (ImGui::GetIO().WantCaptureMouse) return;
}
void _resize_callback(GLFWwindow* window, int width, int height)
{
    screen = vml::vec2(width, height);
}
