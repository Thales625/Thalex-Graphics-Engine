#include "vessel.hpp"

Vessel::Vessel(Mesh* mesh_ptr) : mesh(mesh_ptr) {}

// Update the Vessel
void Vessel::Update(const float delta_time, const float current_time) {
    // for (const auto& engine : this->engines) {
        // engine->Render(m_model, m_view, m_projection);
    // }
}

// Render the Vessel
void Vessel::Render(const glm::mat4 m_model, const glm::mat4 m_view, const glm::mat4 m_projection) {
    mesh->Render(m_model, m_view, m_projection);

    for (const auto& engine : this->engines) {
        engine->Render(m_model, m_view, m_projection);
    }
}