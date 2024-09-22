#include "engine/mesh_renderer.hpp"
#include "engine/mesh.hpp"
#include "engine/material.hpp"

#include <glad/gl.h>

MeshRenderer::MeshRenderer(Mesh* new_mesh, Material* new_material) {
    SetMesh(new_mesh);
    SetMaterial(new_material);
}

// render the mesh
void MeshRenderer::Render(glm::mat4 m_model, glm::mat4 m_view, glm::mat4 m_projection, glm::vec3 sun_dir) {
    material->Use();

    // uniforms
    Shader* shader = material->GetShader();

    // vec3
    shader->SetUniform("sun_dir", sun_dir);

    // mat4
    shader->SetUniform("model", m_model);
    shader->SetUniform("view", m_view);
    shader->SetUniform("projection", m_projection);

    // draw
    mesh->Bind();
    glDrawElements(GL_TRIANGLES, mesh->GetCount(), GL_UNSIGNED_INT, 0);
    mesh->Unbind();
}