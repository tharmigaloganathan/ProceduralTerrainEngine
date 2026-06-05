//
// Created by Tharmiga Loganathan on 2026-06-04.
//

#include "ChunkManager.h"
#include "core/ScopedTimer.h"

// Create the initial loaded chunk set. Multi-chunk loading will expand this later.
//
void ChunkManager::initialize(
    const TerrainSettings& settings,
    PerformanceMetrics& metrics
    ) {
    // Create the initial loaded chunk set. Multi-chunk loading will expand this later.
    //
    activeChunks.clear();

    activeChunks.emplace_back(ChunkCoord{0,0});

    ScopedTimer timer(metrics.terrainGenerationTimeMs);
    activeChunks.back().regenerate(settings, terrainGenerator);
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
}

const std::vector<Chunk>& ChunkManager::chunks() const {
    return activeChunks;
}
