#pragma once

#include <vector>

#include <glm/glm.hpp>

class Mesh {
public:
    struct Vertex {
        glm::vec3 position;
        glm::vec3 normal;
        glm::vec2 tex_coords;

        Vertex(float x, float y, float z) : position(x, y, z) {}
    };

    Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices);

    ~Mesh();

    void Bind() const;

    void Unbind() const;

    unsigned int GetIndexCount() const;

    unsigned int VAO, VBO, EBO;

private:
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;

    void SetupMesh();
};