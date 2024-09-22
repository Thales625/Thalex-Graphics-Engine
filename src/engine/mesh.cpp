#include "engine/mesh.hpp"

#include <glad/gl.h>
#include <glm/fwd.hpp>

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

void Mesh::SetupMesh() {
    // generate buffers/arrays
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    // bind VAO
    glBindVertexArray(VAO);

    // bind and load data into VBO
    glBindBuffer(GL_ARRAY_BUFFER, VBO); 
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);

    // bind and load data into EBO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO); 
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

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


void Mesh::Render(glm::mat4 m_model, glm::mat4 m_view, glm::mat4 m_projection, glm::vec3 sun_dir) {
    // shader
    shader.Use();

    // texture
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture_id);
    shader.SetUniform("texture1", 0);

    // vec3
    shader.SetUniform("sun_dir", sun_dir);

    // mat4
    shader.SetUniform("model", m_model);
    shader.SetUniform("view", m_view);
    shader.SetUniform("projection", m_projection);

    // draw
    Bind();
    glDrawElements(GL_TRIANGLES, GetCount(), GL_UNSIGNED_INT, 0);
    Unbind();
}