#include "engine/game_object.hpp"

GameObject::GameObject(Mesh* mesh_ptr, glm::vec3 new_color) : color(new_color), name("Unnamed GameObject"), mesh(mesh_ptr) {}

// Update the GameObject
void GameObject::Update(const float delta_time, const float current_time) {
    // for (const auto& component : components) {
    //     // Assuming components have an Update() method (dynamic_cast can be used)
    //     if (auto renderer = std::dynamic_pointer_cast<MeshRenderer>(component)) {
    //         renderer->Update(delta_time);
    //     }
    //     // Add checks for other component types as needed
    // }
}

// Render the GameObject
void GameObject::Render(glm::mat4 m_model, glm::mat4 m_view, glm::mat4 m_projection, glm::vec3 sun_dir) {
    mesh->Render(m_model, m_view, m_projection, sun_dir, color);
}