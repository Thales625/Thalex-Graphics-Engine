#include "engine/mesh_renderer.hpp"
#include "engine/mesh.hpp"
#include "engine/material.hpp"

#include <glad/gl.h>

// Constructor
MeshRenderer::MeshRenderer(std::shared_ptr<Mesh> new_mesh, std::shared_ptr<Material> new_material) {
    SetMesh(new_mesh);
    SetMaterial(new_material);
}

// Render the mesh
void MeshRenderer::Render(glm::mat4 m_model, glm::mat4 m_view, glm::mat4 m_projection) {
    material->GetShader()->SetUniform("color", material->GetColor());
    material->GetShader()->SetUniform("model", m_model);
    material->GetShader()->SetUniform("view", m_view);
    material->GetShader()->SetUniform("projection", m_projection);
    material->GetShader()->Use();
    glBindVertexArray(mesh->VAO);
    glDrawElements(GL_TRIANGLES, mesh->GetIndexCount(), GL_UNSIGNED_INT, 0);
}

void MeshRenderer::SetMesh(std::shared_ptr<Mesh> new_mesh) {
    mesh = new_mesh;
}

void MeshRenderer::SetMaterial(std::shared_ptr<Material> new_material) {
    material = new_material;
}