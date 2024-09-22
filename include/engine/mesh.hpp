#pragma once

#include <vector>

#include <glm/glm.hpp>

class Mesh {
public:
    struct Vertex {
        glm::vec3 position;
        glm::vec2 tex_coords;
        glm::vec3 normal;
    };

    Mesh(const std::vector<Vertex> &vertex_array, const std::vector<unsigned int> &index_array) : vertices(vertex_array), indices(index_array) { SetupMesh(); }
    ~Mesh();

    unsigned int GetCount() { return (unsigned int)indices.size(); };

    void Bind() const;
    void Unbind() const;

    unsigned int VAO, VBO, EBO;

private:
    std::vector<Mesh::Vertex> vertices;
    std::vector<unsigned int> indices;

    void SetupMesh();
};