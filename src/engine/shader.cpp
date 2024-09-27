#include "engine/shader.hpp"
#include "utils/utils.hpp"

#include "glad/glad.h"
#include <iostream>

Shader::Shader(const std::string& vertex_path, const std::string& fragment_path) {
    // read the vertex shader source code from file
    std::string vertex_code = ReadFile(vertex_path);
    const char* vertex_source = vertex_code.c_str();

    // read the fragment shader source code from file
    std::string fragment_code = ReadFile(fragment_path);
    const char* fragment_source = fragment_code.c_str();

    // create a vertex shader
    unsigned int vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader, 1, &vertex_source, NULL);
    glCompileShader(vertex_shader);

    // check for vertex shader compile errors
    int success;
    char info_log[512];
    glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertex_shader, 512, NULL, info_log);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << info_log << std::endl;
    }

    // create a fragment shader
    unsigned int fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader, 1, &fragment_source, NULL);
    glCompileShader(fragment_shader);

    // check for fragment shader compile errors
    glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragment_shader, 512, NULL, info_log);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << info_log << std::endl;
    }

    // create a shader program
    shader_program = glCreateProgram();
    glAttachShader(shader_program, vertex_shader);
    glAttachShader(shader_program, fragment_shader);
    glLinkProgram(shader_program);

    // check for shader program link errors
    glGetProgramiv(shader_program, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shader_program, 512, NULL, info_log);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << info_log << std::endl;
    }

    // delete the shaders as they're linked into our program now and no longer necessary
    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);
}

void Shader::SetUniform(const std::string name, const glm::vec3 value) {
    glUniform3fv(glGetUniformLocation(shader_program, name.c_str()), 1, glm::value_ptr(value));
}

void Shader::SetUniform(const std::string name, const glm::mat4 value) {
    glUniformMatrix4fv(glGetUniformLocation(shader_program, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
}

void Shader::SetUniform(const std::string name, const int value) {
    glUniform1i(glGetUniformLocation(shader_program, name.c_str()), value);
}

void Shader::Use() {
    glUseProgram(shader_program);
}