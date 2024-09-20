#pragma once

#include <glm/gtc/type_ptr.hpp>
#include <memory>

#include "engine/window.hpp"

class Camera {
public:
    Camera(glm::vec3 position, float yaw, float pitch);

    glm::mat4 GetViewMatrix() const;
    void ProcessKeyboardInput(std::unique_ptr<Window>& window, float delta_time);
    void ProcessMouseMovement(std::unique_ptr<Window>& window, float delta_time);

private:
    glm::vec3 position, front, up, right;

    float yaw, pitch; // Euler angles

    const glm::vec3 world_up = glm::vec3(0.0f, 1.0f, 0.0f);

    const float mouse_sensitivity = 1.0f;
    double mouse_x=0, mouse_y=0;

    void UpdateCameraVectors();
};