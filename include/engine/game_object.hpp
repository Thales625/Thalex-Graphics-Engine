#pragma once

#include "../../include/engine/transform.hpp"
#include "../../include/engine/mesh_renderer.hpp"

#include <string>

class GameObject {
public:
    // Constructor
    GameObject(std::shared_ptr<Mesh> mesh, std::shared_ptr<Material> material);

    // Set the name of the GameObject
    void SetName(const std::string& name);

    // Get the name of the GameObject
    std::string GetName() const;

    // Update the GameObject
    void Update(const float delta_time);

    // Render the GameObject
    void Render(glm::mat4 m_model, glm::mat4 m_view, glm::mat4 m_projection);

    // Transform
    const Transform GetTransform() const { return transform; };
    void SetTransform(const Transform& new_transform) { transform = new_transform; };
    void SetPosition(glm::vec3 new_position) {transform.position = new_position; };

private:
    std::string name;           // Name of the GameObject
    Transform transform;        // Position, rotation, scale
    MeshRenderer mesh_renderer; // Handles the rendering logic
};