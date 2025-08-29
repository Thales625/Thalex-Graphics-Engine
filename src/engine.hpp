#pragma once

#include "transform.hpp"
#include "mesh.hpp"

class Engine {
public:
    Engine(Mesh* mesh_ptr, float max_gimbal_angle);

    Transform transform; // position, rotation, scale

    void Update();
    inline void Render(const glm::mat4 m_model, const glm::mat4 m_view, const glm::mat4 m_projection) { mesh->Render(m_model, m_view, m_projection); }; 
private:
    Mesh* mesh;
    float max_angle;
};