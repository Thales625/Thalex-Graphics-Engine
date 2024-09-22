#pragma once

#include "engine/shader.hpp"

#include <vector>
#include <glm/glm.hpp>

class Mesh {
public:
    struct Vertex {
        glm::vec3 position;
        glm::vec2 tex_coords;
        glm::vec3 normal;
    };

    Mesh(const std::vector<Vertex> &vertex_array, const std::vector<unsigned int> &index_array, const std::string& vertex_shader_path, const std::string& fragment_shader_path, const unsigned int texture_id) : vertices(vertex_array), indices(index_array), shader(Shader(vertex_shader_path, fragment_shader_path)), texture_id(texture_id) { SetupMesh(); }
    ~Mesh();

    unsigned int GetCount() { return static_cast<unsigned int>(indices.size()); };

    void Bind() const;
    void Unbind() const;

    void Render(glm::mat4 m_model, glm::mat4 m_view, glm::mat4 m_projection, glm::vec3 sun_dir);

    unsigned int VAO, VBO, EBO;

private:
    std::vector<Mesh::Vertex> vertices;
    std::vector<unsigned int> indices;

    Shader shader;
    unsigned int texture_id;

    void SetupMesh();
};