#include "scene.hpp"

#include "transform.hpp"

#include <glm/fwd.hpp>

Scene::Scene() {}

// update all objects in the scene
void Scene::Update(const float delta_time, const float current_time) {
    // update each object
    for (const auto& vessel : this->vessels) {
        vessel->Update(delta_time, current_time);
    }
} 

// render all objects in the scene
void Scene::Render(Window* const window) const {
    glm::mat4 m_model;
    glm::mat4 m_view = camera.GetViewMatrix();
    glm::mat4 m_projection = GetProjectionMatrix(window);

    for (const auto& vessel : this->vessels) {
        m_model = glm::translate(glm::mat4(1.0f), vessel->transform.position);
        m_model = glm::rotate(m_model, vessel->transform.rotation.x, {1.0f, 0.0f, 0.0f}); // pitch
        m_model = glm::rotate(m_model, vessel->transform.rotation.y, {0.0f, 1.0f, 0.0f}); // yaw
        m_model = glm::rotate(m_model, vessel->transform.rotation.z, {0.0f, 0.0f, 1.0f}); // roll
        m_model = glm::scale(m_model, vessel->transform.scale);

        vessel->Render(m_model, m_view, m_projection);
    }

    m_model = glm::translate(glm::mat4(1.0f), this->terrain->transform.position);
    m_model = glm::scale(m_model, this->terrain->transform.scale);
    this->terrain->Render(m_model, m_view, m_projection);
}

glm::mat4 Scene::GetProjectionMatrix(Window* const window) const {
    int width, height;
    window->GetFrameBufferSize(&width, &height);
    return glm::perspective(glm::radians(45.0f), (float)width/(float)height, 0.1f, 1000.0f);
}