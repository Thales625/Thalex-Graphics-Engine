#include "engine/mesh_renderer.hpp"
#include "engine/mesh.hpp"
#include "engine/material.hpp"

#include <glad/gl.h>

MeshRenderer::MeshRenderer(Mesh* new_mesh, Material* new_material) {
    SetMesh(new_mesh);
    SetMaterial(new_material);
}

// render the mesh
void MeshRenderer::Render(glm::mat4 m_model, glm::mat4 m_view, glm::mat4 m_projection) {
    material->Use();

    material->GetShader()->SetUniform("model", m_model);
    material->GetShader()->SetUniform("view", m_view);
    material->GetShader()->SetUniform("projection", m_projection);

    mesh->Bind();
    glDrawElements(GL_TRIANGLES, mesh->GetCount(), GL_UNSIGNED_INT, 0);
    mesh->Unbind();
}