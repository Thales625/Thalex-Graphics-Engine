#include "../../include/engine/camera.hpp"
#include "../../include/engine/window.hpp"

// Constructor
Camera::Camera(glm::vec3 position, float yaw, float pitch)
    : position(position), yaw(yaw), pitch(pitch) {
    UpdateCameraVectors();
}

// Get the view matrix for the camera
glm::mat4 Camera::GetViewMatrix() const {
    return glm::lookAt(position, position + front, up);
}

// Process keyboard input for camera movement
void Camera::ProcessKeyboardInput(std::unique_ptr<Window>& window, float delta_time) {
    const float cameraSpeed = 2.5f * delta_time; // Adjust speed as needed

    if (window->GetKey(GLFW_KEY_W, GLFW_PRESS)) {
        position += front * cameraSpeed;
    }
    if (window->GetKey(GLFW_KEY_S, GLFW_PRESS)) {
        position -= front * cameraSpeed;
    }
    if (window->GetKey(GLFW_KEY_A, GLFW_PRESS)) {
        position -= right * cameraSpeed;
    }
    if (window->GetKey(GLFW_KEY_D, GLFW_PRESS)) {
        position += right * cameraSpeed;
    }

    if (window->GetKey(GLFW_KEY_SPACE, GLFW_PRESS)) {
        position += up * cameraSpeed;
    }
    if (window->GetKey(GLFW_KEY_C, GLFW_PRESS)) {
        position -= up * cameraSpeed;
    }
}

// Process mouse movement for camera orientation
void Camera::ProcessMouseMovement(std::unique_ptr<Window>& window, float delta_time) {
    double mouse_x0 = mouse_x;
    double mouse_y0 = mouse_y;

    window->GetCursorPos(&mouse_x, &mouse_y);

    yaw   += (mouse_x - mouse_x0)*mouse_sensitivity*delta_time;
    pitch -= (mouse_y - mouse_y0)*mouse_sensitivity*delta_time;

    // Constrain pitch, yaw to avoid flipping
    if (pitch > 89.0f) pitch -= 89.0f;
    else if (pitch < -89.0f) pitch = 89.0f;

    if (yaw > 360.0f) yaw -= 360.0f;
    else if (yaw < 0.0f) yaw += 360.0f;

    UpdateCameraVectors();
}

// Update camera vectors based on yaw and pitch
void Camera::UpdateCameraVectors() {
    float rad_yaw = glm::radians(yaw);
    float rad_pitch = glm::radians(pitch);

    front = glm::normalize(glm::vec3(
        cos(rad_yaw) * cos(rad_pitch),
        sin(rad_pitch),
        sin(rad_yaw) * cos(rad_pitch)
    ));

    right = glm::normalize(glm::cross(front, world_up)); // Normalize the right vector
    up = glm::normalize(glm::cross(right, front));       // Normalize the up vector
}