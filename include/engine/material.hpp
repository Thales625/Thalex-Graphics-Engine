#pragma once

#include <glm/glm.hpp>
#include <memory>

#include "engine/shader.hpp"

class Material {
public:
    Material(std::shared_ptr<Shader> shader, const glm::vec3& color = glm::vec3(1.0f));

    void Use() const;

    void SetShader(std::shared_ptr<Shader> new_shader);
    void SetColor(const glm::vec3& new_color);

    std::shared_ptr<Shader> GetShader() const;
    glm::vec3 GetColor() const;
private:
    std::shared_ptr<Shader> shader;
    glm::vec3 color;
};