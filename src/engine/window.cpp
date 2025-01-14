#include "engine/window.hpp"
#include <GLFW/glfw3.h>
#include <iostream>

// IMGUI
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

Window::Window(uint32_t width, uint32_t height, const std::string& title)
    : width(width), height(height), title(title) {}

bool Window::Init() {
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW!" << std::endl;
        return false;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_DEPTH_BITS, 24);

    // create window
    this->glfw_window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
    if (!this->glfw_window) {
        std::cerr << "Failed to create GLFW window!" << std::endl;
        glfwTerminate();
        return false;
    }

    glfwMakeContextCurrent(this->glfw_window);
    glfwSetInputMode(this->glfw_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED); 
    glfwSetFramebufferSizeCallback(this->glfw_window, FrameBufferSizeCallback);
    glfwSetKeyCallback(this->glfw_window, KeyboardCallback);

    // init ImGui
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls

    ImGui_ImplGlfw_InitForOpenGL(glfw_window, true);
    ImGui_ImplOpenGL3_Init();

    // init glad
    if (!gladLoadGL(glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD!" << std::endl;
        return false;
    }

    return true;
}

void FrameBufferSizeCallback(GLFWwindow* const window, int const width, int const height) {
    glViewport(0, 0, width, height);
}

void KeyboardCallback(GLFWwindow* const window, const int key, const int scancode, const int action, const int mods) {
    if (action == 1) { // key down
        // std::cout << key << "\n";

        if  (key == GLFW_KEY_ESCAPE) glfwSetInputMode(window, GLFW_CURSOR, glfwGetInputMode(window, GLFW_CURSOR) == GLFW_CURSOR_DISABLED ? GLFW_CURSOR_NORMAL : GLFW_CURSOR_DISABLED);

        if (key == GLFW_KEY_Q) glfwSetWindowShouldClose(window, true);
    }
}

// close the window and clean up resources
void Window::Close() const {
    if (this->glfw_window) {
        glfwDestroyWindow(this->glfw_window);
        glfwTerminate();
    }

    // close ImGui
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

Window::~Window() {
    Close();
}