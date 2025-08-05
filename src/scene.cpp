#include "scene.hpp"

#include "transform.hpp"

#include <glm/fwd.hpp>

Scene::Scene() : sun_dir({0, 1, 0}) { }

// update all objects in the scene
void Scene::Update(const float delta_time, const float current_time) {
    // sun_dir = glm::vec3(0, glm::cos(current_time), glm::sin(current_time));
    sun_dir = glm::normalize(glm::vec3(0, 2+glm::cos(current_time), glm::sin(current_time)));

    // update each object
    for (const auto& object : game_objects) {
        object->Update(delta_time, current_time);
    }
} 

// render all objects in the scene
void Scene::Render(Window* const window) const {
    glm::mat4 m_model;
    glm::mat4 m_view = camera.GetViewMatrix();
    glm::mat4 m_projection = GetProjectionMatrix(window);

    for (const auto& object : game_objects) {
        m_model = glm::translate(glm::mat4(1.0f), object->transform.position);
        m_model = glm::rotate(m_model, object->transform.rotation.y, {0.0f, 1.0f, 0.0f}); // yaw
        m_model = glm::rotate(m_model, object->transform.rotation.x, {1.0f, 0.0f, 0.0f}); // pitch
        m_model = glm::rotate(m_model, object->transform.rotation.z, {0.0f, 0.0f, 1.0f}); // roll
        m_model = glm::scale(m_model, object->transform.scale);

        object->Render(m_model, m_view, m_projection, sun_dir);
    }
}

glm::mat4 Scene::GetProjectionMatrix(Window* const window) const {
    int width, height;
    window->GetFrameBufferSize(&width, &height);
    return glm::perspective(glm::radians(45.0f), (float)width/(float)height, 0.1f, 100.0f);
}