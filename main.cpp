#define IMGUI_DEFINE_MATH_OPERATORS
#include "gl.h"
#include <GLFW/glfw3.h>
#include <iostream>
#include <imgui.h>
#include <imgui_internal.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <ImNodeFlow.h>

class SimpleSum : public ImFlow::BaseNode
{
public:
    SimpleSum()
    {
        setTitle("Simple sum");
        setStyle(ImFlow::NodeStyle::green());
        ImFlow::BaseNode::addIN<int>("In", 0, ImFlow::ConnectionFilter::SameType());
        ImFlow::BaseNode::addOUT<int>("Out", nullptr)->behaviour([this]() { return getInVal<int>("In") + m_valB; });
    }

    void draw() override
    {
        ImGui::SetNextItemWidth(100.f);
        ImGui::InputInt("##ValB", &m_valB);
    }

private:
    int m_valB = 0;
};

class CollapsingNode : public ImFlow::BaseNode
{
public:
    CollapsingNode()
    {
        setTitle("Collapsing node");
        setStyle(ImFlow::NodeStyle::red());
        ImFlow::BaseNode::addIN<int>("A", 0, ImFlow::ConnectionFilter::SameType());
        ImFlow::BaseNode::addIN<int>("B", 0, ImFlow::ConnectionFilter::SameType());
        ImFlow::BaseNode::addOUT<int>("Out", nullptr)->behaviour([this]() { return getInVal<int>("A") + getInVal<int>("B"); });
    }

    void draw() override
    {
        if (ImFlow::BaseNode::isSelected())
        {
            ImGui::SetNextItemWidth(100.f);
            ImGui::Text("You can only see me when the node is selected!");
        }
    }

};

class ResultNode : public ImFlow::BaseNode
{
public:
    ResultNode()
    {
        setTitle("Result node");
        setStyle(ImFlow::NodeStyle::brown());
        ImFlow::BaseNode::addIN<int>("A", 0, ImFlow::ConnectionFilter::SameType());
        ImFlow::BaseNode::addIN<int>("B", 0, ImFlow::ConnectionFilter::SameType());
    }

    void draw() override
    {
        ImGui::Text("Result: %d", getInVal<int>("A") + getInVal<int>("B"));
    }

};


/* Node editor that sets up the grid to place nodes */
struct NodeEditor : ImFlow::BaseNode
{
    ImFlow::ImNodeFlow mINF;

    NodeEditor(float d, std::size_t r) : BaseNode()
    {
        mINF.setSize({ d, d });
        if (r > 0)
        {
            auto n1 = mINF.addNode<SimpleSum>({ 40, 40 });
            auto n2 = mINF.addNode<SimpleSum>({ 40, 150 });
            auto result = mINF.addNode<ResultNode>({ 250, 80 });

            // Add links between nodes
            n1->outPin("Out")->createLink(result->inPin("A"));
            n2->outPin("Out")->createLink(result->inPin("B"));


            // Add a collapsing node
            auto collapsingNode = mINF.addNode<CollapsingNode>({ 300, 300 });

        }
    }

    void set_size(ImVec2 d)
    {
        mINF.setSize(d);
    }

    void draw() override
    {
        mINF.update();
    }
};



int main(void)
{
    //ax::NodeEditor::EditorContext* editor = nullptr;

    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    if (!gladLoaderLoadGL())
    {
        std::cout << "Failed to initialize OpenGL context" << std::endl;
        return -1;
    }

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(window, true);          // Second param install_callback=true will install GLFW callbacks and chain to existing ones.
    ImGui_ImplOpenGL3_Init();

    NodeEditor* neditor = new NodeEditor(500, 500);

    //editor = ax::NodeEditor::CreateEditor();

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);
        glfwPollEvents();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        ImGui::Begin("Text");
        ImGui::Text("Hello!!!!");
        ImGui::Text("FPS: %.2f (%.2gms)", io.Framerate, io.Framerate ? 1000.0f / io.Framerate : 0.0f);
        ImGui::End();

        ImGui::Separator();

        ImVec2 vMin = ImGui::GetWindowContentRegionMin() + ImVec2(ImGui::GetWindowPos().x, ImGui::GetWindowPos().y);
        ImVec2 vMax = ImGui::GetWindowContentRegionMax() + ImVec2(ImGui::GetWindowPos().x, ImGui::GetWindowPos().y);
        const auto window_size = vMax - vMin; //io.DisplaySize - ImVec2(1, 1);
        const auto node_editor_size = window_size;// - ImVec2(16, 16);
        neditor->set_size(node_editor_size);
        neditor->draw();
        ImGui::GetForegroundDrawList()->AddRect( vMin, vMax, IM_COL32( 255, 255, 0, 255 ) );

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);

    }
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwTerminate();
    return 0;
}