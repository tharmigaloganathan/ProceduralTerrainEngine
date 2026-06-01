//
// Created by Tharmiga Loganathan on 2026-06-01.
//

#ifndef PROCEDURALTERRAINENGINE_MESH_H
#define PROCEDURALTERRAINENGINE_MESH_H

#pragma once

#include <vector>

class Mesh {
public:
    explicit Mesh(const std::vector<float>& vertices);
    ~Mesh();

    Mesh(const Mesh&) = delete;
    Mesh& operator=(const Mesh&) = delete;

    Mesh(Mesh&& other) noexcept;
    Mesh& operator=(Mesh&& other) noexcept;

    void draw() const;

private:
    unsigned int vao = 0;
    unsigned int vbo = 0;
    int vertexCount = 0;
};


#endif //PROCEDURALTERRAINENGINE_MESH_H
