#pragma once

#include "engine/mesh.hpp"
#include "engine/material.hpp"

class MeshRenderer {
public:
    MeshRenderer(Mesh* mesh, Material* material);

    // render the mesh
    void Render(glm::mat4 m_model, glm::mat4 m_view, glm::mat4 m_projection);

    // set the mesh and material
    void SetMesh(Mesh* new_mesh) { mesh = new_mesh; };
    void SetMaterial(Material* new_material) { material = new_material; };

private:
    Mesh* mesh;
    Material* material;
};