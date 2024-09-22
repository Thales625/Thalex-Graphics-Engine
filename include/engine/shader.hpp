#pragma once

#include <string>
#include <iostream>

#include <glm/gtc/type_ptr.hpp>

class Shader {
public:
    Shader(const std::string& vertex_path, const std::string& fragment_path);
    ~Shader() { std::cout << "Shader deconstruct\n"; };

    unsigned int GetProgram() { return m_shaderProgram; }

    void SetUniform(const std::string name, glm::vec3 value);
    void SetUniform(const std::string name, glm::mat4 value);

    void Use();
private:
    unsigned int m_shaderProgram;
};