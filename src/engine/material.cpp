#include "engine/material.hpp"

//Material::Material(Shader* new_shader, const glm::vec3& new_color) : shader(new_shader), color(new_color) {}
Material::Material(Shader* new_shader, const glm::vec3& new_color) : color(new_color) { SetShader(new_shader); }

void Material::Use() const {
    shader->Use();

    shader->SetUniform("color", color);
}