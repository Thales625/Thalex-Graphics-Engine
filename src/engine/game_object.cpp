#include "engine/game_object.hpp"
#include "engine/mesh_renderer.hpp"

GameObject::GameObject(Mesh* mesh, Material* material) : name("Unnamed GameObject"), mesh_renderer(MeshRenderer(mesh, material)) {}

// Update the GameObject
void GameObject::Update(const float delta_time) {
    // for (const auto& component : components) {
    //     // Assuming components have an Update() method (dynamic_cast can be used)
    //     if (auto renderer = std::dynamic_pointer_cast<MeshRenderer>(component)) {
    //         renderer->Update(delta_time);
    //     }
    //     // Add checks for other component types as needed
    // }
}

// Render the GameObject
void GameObject::Render(glm::mat4 m_translate, glm::mat4 m_view, glm::mat4 m_projection) {
    mesh_renderer.Render(m_translate, m_view, m_projection);
}