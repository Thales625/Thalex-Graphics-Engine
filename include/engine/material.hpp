#pragma once

#include <glm/glm.hpp>

#include "engine/shader.hpp"

class Material {
public:
    Material(Shader* new_shader, const glm::vec3& new_color);
    ~Material() { std::cout << "Material deconstruct\n"; };

    void Use() const;

    glm::vec3 GetColor() const { return color; };
    void SetColor(const glm::vec3& new_color) { color = new_color; };

    void SetShader(Shader* new_shader) { shader = new_shader; };
    Shader* GetShader() { return shader; };

private:
    Shader* shader;
    glm::vec3 color;
};