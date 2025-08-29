#pragma once

#include <string>

#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

class Shader {
public:
    Shader(const std::string& vertex_path, const std::string& fragment_path);

    inline GLuint GetProgram() { return shader_program; }

    inline void SetUniform(const std::string name, const glm::vec3 value) const { glUniform3fv(glGetUniformLocation(shader_program, name.c_str()), 1, glm::value_ptr(value)); };
    inline void SetUniform(const std::string name, const glm::mat4 value) const { glUniformMatrix4fv(glGetUniformLocation(shader_program, name.c_str()), 1, GL_FALSE, glm::value_ptr(value)); };
    inline void SetUniform(const std::string name, const int value) const { glUniform1i(glGetUniformLocation(shader_program, name.c_str()), value); }

    inline void Use() const { glUseProgram(shader_program); }
private:
    GLuint shader_program;
};