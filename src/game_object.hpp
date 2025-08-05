#pragma once

#include "transform.hpp"
#include "mesh.hpp"

#include <string>

class GameObject {
public:
    GameObject(Mesh* mesh_ptr, const glm::vec3 n_color = {0, 0, 0});

    Transform transform; // position, rotation, scale
    glm::vec3 color;

    std::string GetName() const { return name; };
    void SetName(const std::string& new_name) { name = new_name; };

    // update the GameObject
    void Update(const float delta_time, const float current_time);

    // render the object
    void Render(glm::mat4 m_model, glm::mat4 m_view, glm::mat4 m_projection, glm::vec3 sun_dir);

private:
    std::string name;
    Mesh* mesh;
};