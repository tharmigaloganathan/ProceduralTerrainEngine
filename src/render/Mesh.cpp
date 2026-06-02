//
// Created by Tharmiga Loganathan on 2026-06-01.
//

#include "Mesh.h"

#include <glad/gl.h>

namespace {
    constexpr int FLOATS_PER_VERTEX = 6;

    // Attribute offsets describe how to read interleaved position/color data from the VBO.
    //
    void configureVertexAttributes() {
        const auto stride = static_cast<GLsizei>(FLOATS_PER_VERTEX * sizeof(float));

        // Position attribute: x, y, z
        // Attribute 0: position, matching `layout(location = 0)` in the vertex shader.
        //
        glVertexAttribPointer(
            0,
            3,
            GL_FLOAT,
            GL_FALSE,
            stride,
            nullptr
        );
        glEnableVertexAttribArray(0);

        // Color attribute: r, g, b
        // Attribute 1: color, matching `layout(location = 1)` in the vertex shader.
        //
        glVertexAttribPointer(
            1,
            3,
            GL_FLOAT,
            GL_FALSE,
            stride,
            reinterpret_cast<void*>(3 * sizeof(float))
        );
        glEnableVertexAttribArray(1);
    }
}
Mesh::Mesh(const std::vector<float>& vertices, unsigned int drawMode)
    : drawMode(drawMode) {
    // Each vertex stores position and colour: 6 floats per vertex.
    //
    vertexCount = static_cast<int>(vertices.size() / 6);

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

    configureVertexAttributes();

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

Mesh::Mesh(
    const std::vector<float>& vertices,
    const std::vector<std::uint32_t>& indices,
    unsigned int drawMode
    )
    : drawMode(drawMode) {
    vertexCount = static_cast<int>(vertices.size() / 6);
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

    configureVertexAttributes();

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