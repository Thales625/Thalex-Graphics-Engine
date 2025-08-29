#pragma once

#include "mesh.hpp"
#include "transform.hpp"
#include "shader.hpp"

#include <vector>
#include <glm/glm.hpp>

class Terrain {
public:
    Terrain(MeshTerrain* mesh_ptr);

    Transform transform; // position, rotation, scale

    void Update(const float delta_time, const float current_time);
    void Render(const glm::mat4 m_model, const glm::mat4 m_view, const glm::mat4 m_projection);
private:
    MeshTerrain* mesh;
};