#pragma once

#include "shader.hpp"

#include <vector>

#include <glm/glm.hpp>

class Mesh {
public:
    struct Vertex {
        glm::vec3 position;
        glm::vec2 tex_coords;
        glm::vec3 normal;
    };

    Mesh(const std::vector<Vertex> &vertex_array, const std::vector<unsigned int> &index_array, const std::string& vertex_shader_path, const std::string& fragment_shader_path, const unsigned int texture_id = 0);
    ~Mesh();

    void Bind() const;
    void Unbind() const;

    void Render(const glm::mat4 m_model, const glm::mat4 m_view, const glm::mat4 m_projection) const;

private:
    Shader shader;
    unsigned int elements_count;
    GLuint texture_id;
    GLuint VAO, VBO, EBO;
};

class MeshTerrain {
public:
    struct Vertex {
        glm::vec3 position;
        glm::vec2 tex_coords;
    };

    MeshTerrain(const std::vector<Vertex> &vertex_array, const std::vector<unsigned int> &index_array, const std::string& vertex_shader_path, const std::string& fragment_shader_path, const unsigned int heightmap_id = 0, const unsigned int texture_id = 0);
    ~MeshTerrain();

    void Bind() const;
    void Unbind() const;

    void Render(const glm::mat4 m_model, const glm::mat4 m_view, const glm::mat4 m_projection) const;

private:
    Shader shader;
    unsigned int elements_count;
    GLuint heightmap_id, texture_id;
    GLuint VAO, VBO, EBO;
};

std::pair<std::vector<MeshTerrain::Vertex>, std::vector<unsigned int>> GenerateGrid(int rows, int cols);