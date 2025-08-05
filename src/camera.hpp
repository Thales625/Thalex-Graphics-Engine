#pragma once

#include <glm/gtc/type_ptr.hpp>

#include "window.hpp"

class Camera {
public:
    Camera();
    Camera(const glm::vec3 new_pos);
    Camera(const glm::vec3 new_pos, const float yaw, const float pitch);
    
    glm::vec3 GetPosition() const { return this->position; };
    void SetPosition(const glm::vec3 new_pos) { position = new_pos; UpdateCameraVectors(); };

    glm::mat4 GetViewMatrix() const;
    void ProcessKeyboardInput(Window* const window, const float delta_time);
    void ProcessMouseMovement(Window* const window, const float delta_time);

    float mouse_sensitivity = 50.0f;
    float camera_speed = 5.0f;

private:
    glm::vec3 position;
    glm::vec3 front, up, right;

    float yaw, pitch;

    const glm::vec3 world_up = {0.0f, 1.0f, 0.0f};

    double mouse_x=0, mouse_y=0;

    void UpdateCameraVectors();
};