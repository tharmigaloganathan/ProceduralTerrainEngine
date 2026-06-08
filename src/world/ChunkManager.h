//
// Created by Tharmiga Loganathan on 2026-06-04.
//

#pragma once

#include "Chunk.h"
#include "ChunkCoord.h"
#include "TerrainGenerator.h"
#include "core/PerformanceMetrics.h"

#include <vector>
#include <unordered_map>

class ChunkManager {
public:
    void initialize(
        ChunkCoord centerCoord,
        const TerrainSettings& settings,
        PerformanceMetrics& metrics
        );

    void updateAroundChunk(
        ChunkCoord centerCoord,
        const TerrainSettings& settings,
        PerformanceMetrics& metrics
        );

    void regenerateAll(const TerrainSettings& settings, PerformanceMetrics& metrics);

    std::vector<const Chunk*> visibleChunks() const;

private:
    void ensureChunksAround(
        ChunkCoord centerCoord,
        const TerrainSettings& settings
        );

    void unloadChunksOutsideRadius(ChunkCoord centerCoord);

    bool isWithinRadius(ChunkCoord coord, ChunkCoord centerCoord) const;

    TerrainGenerator terrainGenerator;

    // Number of chunks loaded outward from the current center chunk.
    // Radius 1 creates a 3x3 grid; radius 2 creates a 5x5 grid.
    //
    int chunkRadius = 1;

    ChunkCoord currentCenterCoord{0,0};
    bool hasInitializedCenter = false;

    // Active chunks keyed by their chunk-space coordinate for fast lookup during streaming.
    //
    std::unordered_map<ChunkCoord, Chunk, ChunkCoordHash> activeChunks;
};

