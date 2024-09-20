#pragma once

#include <memory>

#include "../../include/engine/mesh.hpp"
#include "../../include/engine/material.hpp"

class MeshRenderer {
public:
    // Constructor: takes a Mesh and Material to render
    MeshRenderer(std::shared_ptr<Mesh> mesh, std::shared_ptr<Material> material);

    // Render the mesh
    void Render(glm::mat4 m_model, glm::mat4 m_view, glm::mat4 m_projection);

    // Set the mesh and material
    void SetMesh(std::shared_ptr<Mesh> new_mesh);
    void SetMaterial(std::shared_ptr<Material> new_material);

private:
    // Mesh to render
    std::shared_ptr<Mesh> mesh;

    // Material to apply to the mesh
    std::shared_ptr<Material> material;
};