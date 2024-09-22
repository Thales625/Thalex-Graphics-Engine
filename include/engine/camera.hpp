#pragma once

#include <glm/gtc/type_ptr.hpp>

#include "engine/window.hpp"

class Camera {
public:
    Camera(glm::vec3 position, float yaw, float pitch);

    glm::mat4 GetViewMatrix() const;
    void ProcessKeyboardInput(Window* window, float delta_time);
    void ProcessMouseMovement(Window* window, float delta_time);

    float camera_speed, mouse_sensitivity;
private:
    glm::vec3 position, front, up, right;

    float yaw, pitch;

    const glm::vec3 world_up = glm::vec3(0.0f, 1.0f, 0.0f);

    double mouse_x=0, mouse_y=0;

    void UpdateCameraVectors();
};