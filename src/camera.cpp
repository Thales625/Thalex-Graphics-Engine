#include "camera.hpp"
#include "window.hpp"

#include "imgui.h"
#include <GLFW/glfw3.h>

Camera::Camera() : position(glm::vec3(0)), yaw(0), pitch(0) {
    UpdateCameraVectors();
}

Camera::Camera(const glm::vec3 new_pos) : position(new_pos), yaw(0), pitch(0) {
    UpdateCameraVectors();
}

Camera::Camera(const glm::vec3 new_pos, const float yaw, const float pitch) : position(new_pos), yaw(yaw), pitch(pitch) {
    UpdateCameraVectors();
}

glm::mat4 Camera::GetViewMatrix() const {
    return glm::lookAt(position, position + front, up);
}

void Camera::ProcessKeyboardInput(Window* window, float delta_time) {
    if (ImGui::GetIO().WantCaptureKeyboard) return;

    // movement
    const float speed = camera_speed * delta_time;

    if (window->GetKey(GLFW_KEY_W, GLFW_PRESS)) {
        position += front * speed;
    }
    if (window->GetKey(GLFW_KEY_S, GLFW_PRESS)) {
        position -= front * speed;
    }
    if (window->GetKey(GLFW_KEY_A, GLFW_PRESS)) {
        position -= right * speed;
    }
    if (window->GetKey(GLFW_KEY_D, GLFW_PRESS)) {
        position += right * speed;
    }

    if (window->GetKey(GLFW_KEY_SPACE, GLFW_PRESS)) {
        position += world_up * speed;
    }
    if (window->GetKey(GLFW_KEY_C, GLFW_PRESS)) {
        position -= world_up * speed;
    }
}

void Camera::ProcessMouseMovement(Window* const window, const float delta_time) {
    if (window->GetInputMode() != GLFW_CURSOR_DISABLED || ImGui::GetIO().WantCaptureKeyboard) return;

    double mouse_x0 = mouse_x;
    double mouse_y0 = mouse_y;

    window->GetCursorPos(&mouse_x, &mouse_y);

    yaw   += (mouse_x - mouse_x0)*mouse_sensitivity*delta_time;
    pitch -= (mouse_y - mouse_y0)*mouse_sensitivity*delta_time;

    // clamp pitch
    if (pitch > 89.0f) pitch = 89.0f;
    else if (pitch < -89.0f) pitch = -89.0f;

    if (yaw > 360.0f) yaw -= 360.0f;
    else if (yaw < 0.0f) yaw += 360.0f;

    UpdateCameraVectors();
}

void Camera::UpdateCameraVectors() {
    float rad_yaw = glm::radians(yaw);
    float rad_pitch = glm::radians(pitch);

    front = glm::normalize(glm::vec3(
        cos(rad_yaw) * cos(rad_pitch),
        sin(rad_pitch),
        sin(rad_yaw) * cos(rad_pitch)
    ));

    right = glm::normalize(glm::cross(front, world_up));
    up = glm::normalize(glm::cross(right, front));
}