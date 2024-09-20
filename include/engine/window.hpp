#pragma once

#include <cstdint>
#include <glad/gl.h>
#include <GLFW/glfw3.h>

#include <string>

void FrameBufferSizeCallback(GLFWwindow* window, int width, int height);

class Window {
public:
    Window(uint32_t width, uint32_t height, const std::string& title);
    ~Window();
    
    bool Init();
    bool ShouldClose() const;
    void Close() const;
    void SwapBuffers() const;
    void PollEvents() const;
    int GetKey(int key, int action) { return glfwGetKey(glfw_window, key) == action; }
    void GetCursorPos(double* xpos, double* ypos) { glfwGetCursorPos(glfw_window, xpos, ypos); }
    void GetFrameBufferSize(int* width, int* height) { glfwGetFramebufferSize(glfw_window, width, height); }
private:
    GLFWwindow* glfw_window;
    int width, height;
    std::string title;
};