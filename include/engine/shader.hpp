#pragma once

#include <string>

#include <glm/gtc/type_ptr.hpp>

class Shader {
public:
    Shader(const std::string& vertex_path, const std::string& fragment_path);

    unsigned int GetProgram() { return m_shaderProgram; }

    void SetUniform(const std::string name, const glm::vec3 value);
    void SetUniform(const std::string name, const glm::mat4 value);
    void SetUniform(const std::string name, const int value);

    void Use();
private:
    unsigned int m_shaderProgram;
};