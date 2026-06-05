//
// Created by Tharmiga Loganathan on 2026-06-04.
//

#include "Chunk.h"

#include <glad/gl.h>

Chunk::Chunk(ChunkCoord coord)
    : chunkCoord(coord) {}

void Chunk::regenerate(const TerrainSettings& settings, TerrainGenerator& generator) {
    TerrainMeshData meshData = generator.generate(settings, chunkCoord);

    mesh = std::make_unique<Mesh>(
        meshData.vertices,
        meshData.indices,
        GL_TRIANGLES
        );
}

void Chunk::draw() const {
    if (mesh != nullptr) {
        mesh->draw();
    }
}

ChunkCoord Chunk::coord() const {
    return chunkCoord;
}
