//
// Created by Tharmiga Loganathan on 2026-06-01.
//

#include "Mesh.h"

#include <glad/gl.h>

Mesh::Mesh(const std::vector<float>& vertices, unsigned int drawMode)
    : drawMode(drawMode) {
    // Stores only positions for now: 3 floats per vertex.
    //
    vertexCount = static_cast<int>(vertices.size() / 3);

    // A VAO stores the vertex attribute layout; a VBO stores the actual vertex data.
    //
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);

    glBindVertexArray(vao);

    // Upload vertex position data to the GPU.
    //
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(
        GL_ARRAY_BUFFER,
        static_cast<GLsizeiptr>(vertices.size() * sizeof(float)),
        vertices.data(),
        GL_STATIC_DRAW
        );

    // Attribute location 0 matches `layout(location = 0)` in basic.vert.
    //
    glVertexAttribPointer(
        0,
        3,
        GL_FLOAT,
        GL_FALSE,
        3 * sizeof(float),
        nullptr
        );

    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

Mesh::Mesh(
    const std::vector<float>& vertices,
    const std::vector<std::uint32_t>& indices,
    unsigned int drawMode
    )
    : drawMode(drawMode) {
    vertexCount = static_cast<int>(vertices.size() / 3);
    indexCount = static_cast<int>(indices.size());

    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ebo);

    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(
        GL_ARRAY_BUFFER,
        static_cast<GLsizeiptr>(vertices.size() * sizeof(float)),
        vertices.data(),
        GL_STATIC_DRAW
        );

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,ebo);
    glBufferData(
        GL_ELEMENT_ARRAY_BUFFER,
        static_cast<GLsizeiptr>(indices.size() * sizeof(std::uint32_t)),
        indices.data(),
        GL_STATIC_DRAW
        );

    glVertexAttribPointer(
        0,
        3,
        GL_FLOAT,
        GL_FALSE,
        3 * sizeof(float),
        nullptr
        );

    glEnableVertexAttribArray(0);

    glBindVertexArray(0);
}

// RAII cleanup: Mesh owns the GPU buffers used for this geometry.
//
Mesh::~Mesh() {
    if (ebo != 0) {
        glDeleteBuffers(1, &ebo);
    }

    if (vbo != 0) {
        glDeleteBuffers(1, &vbo);
    }

    if (vao != 0) {
        glDeleteVertexArrays(1, &vao);
    }
}

// Move ownership of GPU buffer IDs and clear the source so it does not delete them.
//
Mesh::Mesh(Mesh&& other) noexcept
    : vao(other.vao),
      vbo(other.vbo),
      ebo(other.ebo),
      drawMode(other.drawMode),
      vertexCount(other.vertexCount),
      indexCount(other.indexCount) {
    other.vao = 0;
    other.vbo = 0;
    other.ebo = 0;
    other.drawMode = 0;
    other.vertexCount = 0;
    other.indexCount = 0;
}

Mesh& Mesh::operator=(Mesh&& other) noexcept {
    if (this != &other) {
        if (ebo != 0) {
            glDeleteBuffers(1, &ebo);
        }

        if (vbo != 0) {
            glDeleteBuffers(1, &vbo);
        }

        if (vao != 0) {
            glDeleteVertexArrays(1, &vao);
        }

        vao = other.vao;
        vbo = other.vbo;
        ebo = other.ebo;
        drawMode = other.drawMode;
        vertexCount = other.vertexCount;
        indexCount = other.indexCount;

        other.vao = 0;
        other.vbo = 0;
        other.ebo = 0;
        other.drawMode = 0;
        other.vertexCount = 0;
        other.indexCount = 0;
    }

    return *this;
}

void Mesh::draw() const {
    glBindVertexArray(vao);

    if (indexCount > 0) {
        glDrawElements(drawMode, indexCount, GL_UNSIGNED_INT, nullptr);
    } else {
        glDrawArrays(drawMode, 0, vertexCount);
    }
    glBindVertexArray(0);
}