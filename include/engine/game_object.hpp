#pragma once

#include "engine/transform.hpp"
#include "engine/mesh.hpp"

#include <string>

class GameObject {
public:
    GameObject(Mesh* mesh_ptr);

    Transform transform; // position, rotation, scale

    std::string GetName() const { return name; };
    void SetName(const std::string& new_name) { name = new_name; };

    // update the GameObject
    void Update(const float delta_time);

    // render the object
    void Render(glm::mat4 m_model, glm::mat4 m_view, glm::mat4 m_projection, glm::vec3 sun_dir);

    // transform
    const Transform GetTransform() const { return transform; };
    void SetTransform(const Transform& new_transform) { transform = new_transform; };

private:
    std::string name;
    Mesh* mesh;
};