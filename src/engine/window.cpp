#include "engine/window.hpp"

#include <iostream>

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
    glfw_window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
    if (!glfw_window) {
        std::cerr << "Failed to create GLFW window!" << std::endl;
        glfwTerminate();
        return false;
    }

    glfwMakeContextCurrent(glfw_window);
    glfwSetInputMode(glfw_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED); 
    glfwSetFramebufferSizeCallback(glfw_window, FrameBufferSizeCallback);

    // init glad
    if (!gladLoadGL(glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD!" << std::endl;
        return false;
    }

    return true;
}

void FrameBufferSizeCallback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

// close the window and clean up resources
void Window::Close() const {
    if (glfw_window) {
        glfwDestroyWindow(glfw_window);
        glfwTerminate();
    }
}

Window::~Window() {
    Close();
}