#include "mesh.hpp"

#include "glad/glad.h"

// constructor
Mesh::Mesh(const std::vector<Vertex> &vertex_array, const std::vector<unsigned int> &index_array, const std::string& vertex_shader_path, const std::string& fragment_shader_path, const unsigned int texture_id) 
    : shader(Shader(vertex_shader_path, fragment_shader_path)), texture_id(texture_id), elements_count(index_array.size()) {
    // generate buffers/arrays
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    // bind VAO
    glBindVertexArray(VAO);

    // bind and load data into VBO
    glBindBuffer(GL_ARRAY_BUFFER, VBO); 
    glBufferData(GL_ARRAY_BUFFER, vertex_array.size() * sizeof(Vertex), vertex_array.data(), GL_STATIC_DRAW);

    // bind and load data into EBO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO); 
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_array.size() * sizeof(unsigned int), index_array.data(), GL_STATIC_DRAW);

    // specify position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
    glEnableVertexAttribArray(0);

    // specify texture coordinate
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, tex_coords));
    glEnableVertexAttribArray(1);

    // specify normal attribute
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
    glEnableVertexAttribArray(2);

    // unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0); 
    glBindVertexArray(0);
}

// deconstructor
Mesh::~Mesh() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}

// bind VAO
void Mesh::Bind() const {
    glBindVertexArray(VAO);
}

// unbind VAO
void Mesh::Unbind() const {
    glBindVertexArray(0);
}

void Mesh::Render(const glm::mat4 m_model, const glm::mat4 m_view, const glm::mat4 m_projection) const {
    // shader
    shader.Use();

    // texture
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture_id);
    shader.SetUniform("texture1", 0);

    // mat4
    shader.SetUniform("model", m_model);
    shader.SetUniform("view", m_view);
    shader.SetUniform("projection", m_projection);

    // draw
    Bind();
    glDrawElements(GL_TRIANGLES, elements_count, GL_UNSIGNED_INT, 0);
    Unbind();
}



// constructor
MeshTerrain::MeshTerrain(const std::vector<Vertex> &vertex_array, const std::vector<unsigned int> &index_array, const std::string& vertex_shader_path, const std::string& fragment_shader_path, const unsigned int heightmap_id, const unsigned int texture_id) 
    : shader(Shader(vertex_shader_path, fragment_shader_path)), heightmap_id(heightmap_id), texture_id(texture_id), elements_count(index_array.size()) {
    // generate buffers/arrays
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    // bind VAO
    glBindVertexArray(VAO);

    // bind and load data into VBO
    glBindBuffer(GL_ARRAY_BUFFER, VBO); 
    glBufferData(GL_ARRAY_BUFFER, vertex_array.size() * sizeof(Vertex), vertex_array.data(), GL_STATIC_DRAW);

    // bind and load data into EBO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO); 
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_array.size() * sizeof(unsigned int), index_array.data(), GL_STATIC_DRAW);

    // specify position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
    glEnableVertexAttribArray(0);

    // specify texture coordinate
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, tex_coords));
    glEnableVertexAttribArray(1);

    // unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0); 
    glBindVertexArray(0);
}

// deconstructor
MeshTerrain::~MeshTerrain() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}

// bind VAO
void MeshTerrain::Bind() const {
    glBindVertexArray(VAO);
}

// unbind VAO
void MeshTerrain::Unbind() const {
    glBindVertexArray(0);
}

void MeshTerrain::Render(const glm::mat4 m_model, const glm::mat4 m_view, const glm::mat4 m_projection) const {
    // shader
    shader.Use();

    // heightmap
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, heightmap_id);
    shader.SetUniform("heightmap", 1);

    // texture
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture_id);
    shader.SetUniform("texture_id", 0);

    // mat4
    shader.SetUniform("model", m_model);
    shader.SetUniform("view", m_view);
    shader.SetUniform("projection", m_projection);

    // draw
    Bind();
    glDrawElements(GL_TRIANGLES, elements_count, GL_UNSIGNED_INT, 0);
    Unbind();
}

std::pair<std::vector<MeshTerrain::Vertex>, std::vector<unsigned int>> GenerateGrid(int rows, int cols) {
    std::vector<MeshTerrain::Vertex> vertices;
    std::vector<unsigned int> indices;

    // generate vertices
    for (int r = 0; r <= rows; r++) {
        for (int c = 0; c <= cols; c++) {
            float x = -1.0f + 2.0f * (float)c / (float)cols;
            float z = -1.0f + 2.0f * (float)r / (float)rows;
            float u = (float)c / (float)cols;
            float v = (float)r / (float)rows;

            vertices.push_back({{x, 0.0f, z}, {u, v}});
        }
    }

    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            int i0 = r * (cols + 1) + c;
            int i1 = i0 + 1;
            int i2 = i0 + (cols + 1);
            int i3 = i2 + 1;

            // triangles
            indices.push_back(i0);
            indices.push_back(i2);
            indices.push_back(i1);

            indices.push_back(i2);
            indices.push_back(i3);
            indices.push_back(i1);
        }
    }

    return {vertices, indices};
}