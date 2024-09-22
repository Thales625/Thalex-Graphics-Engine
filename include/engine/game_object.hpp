#pragma once

#include "engine/transform.hpp"
#include "engine/mesh_renderer.hpp"

#include <string>

class GameObject {
public:
    GameObject(Mesh* mesh, Material* material);
    ~GameObject() { std::cout << "GameObject deconstruct\n"; };

    Transform transform; // position, rotation, scale

    std::string GetName() const { return name; };
    void SetName(const std::string& new_name) { name = new_name; };

    // Update the GameObject
    void Update(const float delta_time);

    // Render the GameObject
    void Render(glm::mat4 m_model, glm::mat4 m_view, glm::mat4 m_projection);

    // Transform
    const Transform GetTransform() const { return transform; };
    void SetTransform(const Transform& new_transform) { transform = new_transform; };

private:
    std::string name;           // Name of the GameObject
    MeshRenderer mesh_renderer; // Handles the rendering logic
};