//
// Created by Tharmiga Loganathan on 2026-06-04.
//

#pragma once

#include "render/Mesh.h"
#include "world/ChunkCoord.h"
#include "world/TerrainGenerator.h"

#include <memory>

class Shader;

class Chunk {
public:
    explicit Chunk(ChunkCoord coord);

    void regenerate(const TerrainSettings& settings, TerrainGenerator& generate);
    void draw() const;

    ChunkCoord coord() const;

private:
    ChunkCoord chunkCoord;

    // Each chunk owns it's renderable terrain mesh.
    //
    std::unique_ptr<Mesh> mesh;
};

