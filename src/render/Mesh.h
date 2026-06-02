//
// Created by Tharmiga Loganathan on 2026-06-01.
//

#pragma once

#include <cstdint>
#include <vector>

class Mesh {
public:
    Mesh(
        const std::vector<float>& vertices,
        const std::vector<std::uint32_t>& indices,
        unsigned int drawMode
        );
    Mesh(const std::vector<float>& vertices, unsigned int drawMode);
    ~Mesh();

    Mesh(const Mesh&) = delete;
    Mesh& operator=(const Mesh&) = delete;

    Mesh(Mesh&& other) noexcept;
    Mesh& operator=(Mesh&& other) noexcept;

    void draw() const;

private:
    unsigned int vao = 0;
    unsigned int vbo = 0;
    unsigned int ebo = 0;

    unsigned int drawMode = 0;

    int vertexCount = 0;
    int indexCount = 0;
};

