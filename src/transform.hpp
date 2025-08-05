#pragma once

#include <glm/glm.hpp>

struct Transform {
    glm::vec3 position;
    glm::vec3 rotation;
    glm::vec3 scale;

    Transform() : position(0.0f), rotation(0.0f), scale(1.0f) {}
    Transform(glm::vec3 pos) : position(pos), rotation(0.0f), scale(1.0f) {}
};