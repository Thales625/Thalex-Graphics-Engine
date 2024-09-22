#include "engine/scene.hpp"
#include "engine/transform.hpp"
#include <glm/fwd.hpp>

Scene::Scene(Camera* new_camera) : sun_dir(glm::vec3(0, 1, 0)), camera(new_camera) {}

void Scene::AddGameObject(GameObject* object) {
    game_objects.push_back(object);
}

// update all objects in the scene
void Scene::Update(float delta_time) const {
    // sun_dir += delta_time;

    for (auto& object : game_objects) {
        object->Update(delta_time);
    }
} 

// render all objects in the scene
void Scene::Render(Window* window) const {
    Transform transform;

    glm::mat4 m_model;
    glm::mat4 m_view = camera->GetViewMatrix();
    glm::mat4 m_projection = GetProjectionMatrix(window);

    for (auto& object : game_objects) {
        transform = object->GetTransform();

        m_model = glm::translate(glm::mat4(1.0f), transform.position);
        m_model = glm::rotate(m_model, transform.rotation.y, glm::vec3(0.0f, 1.0f, 0.0f)); // yaw
        m_model = glm::rotate(m_model, transform.rotation.x, glm::vec3(1.0f, 0.0f, 0.0f)); // pitch
        m_model = glm::rotate(m_model, transform.rotation.z, glm::vec3(0.0f, 0.0f, 1.0f)); // roll
        m_model = glm::scale(m_model, transform.scale);

        object->Render(m_model, m_view, m_projection, sun_dir);
    }
}

glm::mat4 Scene::GetProjectionMatrix(Window* window) const {
    int width, height;
    window->GetFrameBufferSize(&width, &height);
    return glm::perspective(glm::radians(45.0f), (float)width/(float)height, 0.1f, 100.0f);
}