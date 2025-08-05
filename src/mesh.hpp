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

    void Render(glm::mat4 m_model, glm::mat4 m_view, glm::mat4 m_projection, glm::vec3 sun_dir, glm::vec3 color);

private:
    Shader shader;
    unsigned int texture_id;
    unsigned int elements_count;
    unsigned int VAO, VBO, EBO;
};