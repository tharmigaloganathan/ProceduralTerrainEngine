//
// Created by Tharmiga Loganathan on 2026-06-04.
//

#pragma once

#include "Chunk.h"
#include "TerrainGenerator.h"
#include "core/PerformanceMetrics.h"

#include <vector>

class ChunkManager {
public:
    void initialize(const TerrainSettings& settings, PerformanceMetrics& metrics);
    void regenerateAll(const TerrainSettings& settings, PerformanceMetrics& metrics);

    const std::vector<Chunk>& chunks() const;

private:
    void createChunkGrid(const TerrainSettings& settings);

    TerrainGenerator terrainGenerator;

    // Number of chunks loaded outward from the origin.
    // Radius 1 creates a 3x3 grid; radius 2 creates a 5x5 grid.
    //
    int chunkRadius = 1;

    // Active chunks currently loaded in the world.
    //
    std::vector<Chunk> activeChunks;
};

