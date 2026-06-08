//
// Created by Tharmiga Loganathan on 2026-06-04.
//

#include "ChunkManager.h"
#include "core/ScopedTimer.h"

void ChunkManager::initialize(
    ChunkCoord centerCoord,
    const TerrainSettings& settings,
    PerformanceMetrics& metrics
    ) {
    activeChunks.clear();

    {
        // Measure the total cost of generating the initial chunk region.
        //
        ScopedTimer timer(metrics.terrainGenerationTimeMs);
        ensureChunksAround(centerCoord, settings);
    }

    currentCenterCoord = centerCoord;
    hasInitializedCenter = true;
    metrics.activeChunkCount = static_cast<int>(activeChunks.size());
}

void ChunkManager::updateAroundChunk(
    ChunkCoord centerCoord,
    const TerrainSettings& settings,
    PerformanceMetrics& metrics
    ) {
    // While this function may be invoked with every frame, chunk ctreaming only does
    // real work when the camera crosses a chunk boundary.
    //
    if (hasInitializedCenter && centerCoord == currentCenterCoord) {
        return;
    }

    {
        // Measure only the work needed to shift the active chunk region.
        //
        ScopedTimer timer(metrics.terrainGenerationTimeMs);

        unloadChunksOutsideRadius(centerCoord);
        ensureChunksAround(centerCoord, settings);
    }

    currentCenterCoord = centerCoord;
    hasInitializedCenter = true;
    metrics.activeChunkCount = static_cast<int>(activeChunks.size());
}

void ChunkManager::regenerateAll(
    const TerrainSettings& settings,
    PerformanceMetrics& metrics
    ) {
    // Regenerate every active chunk using the current terrain settings.
    //
    ScopedTimer timer(metrics.terrainGenerationTimeMs);

    for (auto& [coord, chunk]: activeChunks) {
        chunk.regenerate(settings, terrainGenerator);
    }

    metrics.activeChunkCount = static_cast<int>(activeChunks.size());
}

std::vector<const Chunk*> ChunkManager::visibleChunks() const {
    std::vector<const Chunk*> result;
    result.reserve(activeChunks.size());

    for (const auto& [coord, chunk] : activeChunks) {
        result.push_back(&chunk);
    }

    return result;
}

void ChunkManager::ensureChunksAround(
    ChunkCoord centerCoord,
    const TerrainSettings& settings
    ) {
    // Ensure every chunk in the square loading radius exists.
    //
    for (int z = centerCoord.z - chunkRadius; z <= centerCoord.z + chunkRadius; ++z) {
        for (int x = centerCoord.x - chunkRadius; x <= centerCoord.x + chunkRadius; ++x) {
            ChunkCoord coord{x,z};

            if (activeChunks.find(coord) != activeChunks.end()) {
                continue;
            }

            Chunk chunk(coord);
            chunk.regenerate(settings,terrainGenerator);

            activeChunks.emplace(coord, std::move(chunk));
        }
    }
}

void ChunkManager::unloadChunksOutsideRadius(ChunkCoord centerCoord) {
    // Remove chunks that are no longer inside the active loading radius.
    //
    for (auto it = activeChunks.begin(); it != activeChunks.end(); ) {
        if (isWithinRadius(it->first, centerCoord)) {
            ++it;
        } else {
            it = activeChunks.erase(it);
        }
    }
}

bool ChunkManager::isWithinRadius(ChunkCoord coord, ChunkCoord centerCoord) const {
    const int dx = std::abs(coord.x - centerCoord.x);
    const int dz = std::abs(coord.z - centerCoord.z);

    return dx <= chunkRadius && dz <= chunkRadius;
}