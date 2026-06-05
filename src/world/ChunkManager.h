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
    TerrainGenerator terrainGenerator;

    // Active chunks currently loaded in the world. For now we will only have the origin chunk.
    //
    std::vector<Chunk> activeChunks;
};

