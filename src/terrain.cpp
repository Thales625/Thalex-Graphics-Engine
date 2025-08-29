#include "terrain.hpp"

Terrain::Terrain(MeshTerrain* mesh_ptr) : mesh(mesh_ptr) {}

// Update the Terrain
void Terrain::Update(const float delta_time, const float current_time) {}

// Render the Terrain
void Terrain::Render(const glm::mat4 m_model, const glm::mat4 m_view, const glm::mat4 m_projection) {
    mesh->Render(m_model, m_view, m_projection);
}