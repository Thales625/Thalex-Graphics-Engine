#include "engine/material.hpp"
#include <memory>

Material::Material(std::shared_ptr<Shader> shader, const glm::vec3& color)
    : shader(shader), color(color) {}

void Material::Use() const {
    shader->Use();

    shader->SetUniform("color", color);
}

void Material::SetShader(std::shared_ptr<Shader> new_shader) {
    shader = new_shader;
}

void Material::SetColor(const glm::vec3& new_color) {
    color = new_color;
}

std::shared_ptr<Shader> Material::GetShader() const { return shader; }
glm::vec3 Material::GetColor() const { return color; }