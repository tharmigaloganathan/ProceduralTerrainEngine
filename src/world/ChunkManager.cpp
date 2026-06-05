//
// Created by Tharmiga Loganathan on 2026-06-04.
//

#include "ChunkManager.h"
#include "core/ScopedTimer.h"

void ChunkManager::initialize(
    const TerrainSettings& settings,
    PerformanceMetrics& metrics
    ) {
    // Create the initial loaded chunk set. Camera-based loading will replace this later.
    //
    activeChunks.clear();

    {
        // Measure the total cost of generating the initial chunk region.
        //
        ScopedTimer timer(metrics.terrainGenerationTimeMs);
        createChunkGrid(settings);
    }

    metrics.activeChunkCount = static_cast<int>(activeChunks.size());
}

void ChunkManager::regenerateAll(
    const TerrainSettings& settings,
    PerformanceMetrics& metrics
    ) {
    // Regenerate every active chunk using the current terrain settings.
    //
    ScopedTimer timer(metrics.terrainGenerationTimeMs);

    for (Chunk& chunk : activeChunks) {
        chunk.regenerate(settings, terrainGenerator);
    }

    metrics.activeChunkCount = static_cast<int>(activeChunks.size());
}

const std::vector<Chunk>& ChunkManager::chunks() const {
    return activeChunks;
}

void ChunkManager::createChunkGrid(const TerrainSettings& settings) {
    // Build a square chunk region centered on the origin.
    //
    for (int z = -chunkRadius; z <= chunkRadius; ++z) {
        for (int x = -chunkRadius; x <= chunkRadius; ++x) {
            activeChunks.emplace_back(ChunkCoord{x, z});
            activeChunks.back().regenerate(settings, terrainGenerator);
        }
    }
}