#pragma once

#include "transform.hpp"
#include "mesh.hpp"
#include "engine.hpp"

#include <vector>

class Vessel {
public:
    Vessel(Mesh* mesh_ptr);

    Transform transform; // position, rotation, scale

    inline Engine* AddEngine(Engine *n_engine) { engines.push_back(n_engine); return n_engine; };

    void Update(const float delta_time, const float current_time);
    void Render(const glm::mat4 m_model, const glm::mat4 m_view, const glm::mat4 m_projection);
private:
    Mesh* mesh;
    std::vector<Engine*> engines;
};