#include "engine/game_object.hpp"
#include "engine/mesh_renderer.hpp"
#include "engine/transform.hpp"

#include <memory>

// Constructor
GameObject::GameObject(std::shared_ptr<Mesh> mesh, std::shared_ptr<Material> material) 
    : name("Unnamed GameObject"),
    transform(Transform()),
    mesh_renderer(MeshRenderer(mesh, material)) {}

// Set the name of the GameObject
void GameObject::SetName(const std::string& name) {
    this->name = name;
}

// Get the name of the GameObject
std::string GameObject::GetName() const {
    return name;
}

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