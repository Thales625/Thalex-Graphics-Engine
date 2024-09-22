#include "engine/material.hpp"

#include <glad/gl.h>

Material::Material(Shader* new_shader, const glm::vec3& new_color, const unsigned int new_texture_id) : shader(new_shader), color(new_color), texture_id(new_texture_id) {}

void Material::Use() const {
    shader->Use();

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture_id);

    shader->SetUniform("color", color);
    shader->SetUniform("texture1", 0);
}