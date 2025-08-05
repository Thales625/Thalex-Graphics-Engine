#pragma once

#include <string>

#include "glad/glad.h"

#include <GLFW/glfw3.h>


void FrameBufferSizeCallback(GLFWwindow* const window, int const width, int const height);
void KeyboardCallback(GLFWwindow* const window, const int key, const int scancode, const int action, const int mods);

class Window {
public:
    Window(uint32_t width, uint32_t height, const std::string& title);
    ~Window();
    
    bool Init();

    bool GetShouldClose() const { return glfwWindowShouldClose(glfw_window); };
    void SetShouldClose(const bool value) const { glfwSetWindowShouldClose(glfw_window, value); };
    void Close() const;

    void SwapBuffers() const { glfwSwapBuffers(glfw_window); };
    void PollEvents() const { glfwPollEvents(); };

    bool GetKey(const int key, const int action) const { return glfwGetKey(glfw_window, key) == action; }
    void GetCursorPos(double* const xpos, double* const ypos) const { glfwGetCursorPos(glfw_window, xpos, ypos); }
    void GetFrameBufferSize(int* const width, int* const height) const { glfwGetFramebufferSize(glfw_window, width, height); }

    GLFWwindow* GetGlfwWindow() const { return this->glfw_window; };
    int GetInputMode() const { return glfwGetInputMode(this->glfw_window, GLFW_CURSOR); };
private:
    GLFWwindow* glfw_window;
    int width, height;
    std::string title;
};