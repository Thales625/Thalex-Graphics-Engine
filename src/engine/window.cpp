#include "engine/window.hpp"

#include <cstdint>
#include <iostream>

// Constructor: initialize GLFW and create a window
Window::Window(uint32_t width, uint32_t height, const std::string& title)
    : width(width), height(height), title(title) {}

// Initialize the window and OpenGL context
bool Window::Init() {
    // Initialize GLFW
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW!" << std::endl;
        return false;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_DEPTH_BITS, 24);

    // Create a windowed mode window and its OpenGL context
    glfw_window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
    if (!glfw_window) {
        std::cerr << "Failed to create GLFW window!" << std::endl;
        glfwTerminate();
        return false;
    }

    // Make the window's context current
    glfwMakeContextCurrent(glfw_window);
    glfwSetInputMode(glfw_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED); 
    glfwSetFramebufferSizeCallback(glfw_window, FrameBufferSizeCallback);

    // Initialize GLAD (load OpenGL function pointers)
    if (!gladLoadGL(glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD!" << std::endl;
        return false;
    }

    return true;
}

void FrameBufferSizeCallback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

// Poll for input events
void Window::PollEvents() const {
    glfwPollEvents();
}

// Swap the front and back buffers
void Window::SwapBuffers() const {
    glfwSwapBuffers(glfw_window);
}

// Check if the window should close
bool Window::ShouldClose() const {
    return glfwWindowShouldClose(glfw_window);
}

// Close the window and clean up resources
void Window::Close() const {
    if (glfw_window) {
        glfwDestroyWindow(glfw_window);
        glfwTerminate();
    }
}

Window::~Window() {
    Close();
}