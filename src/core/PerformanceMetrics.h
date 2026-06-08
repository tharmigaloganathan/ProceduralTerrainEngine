//
// Created by Tharmiga Loganathan on 2026-06-04.
//

#pragma once

// Shared performance counters collected by the app/renderer and later displayed in debug UI.
//
struct PerformanceMetrics {
    float frameTimeMs = 0.0f;
    float fps = 0.0f;
    float terrainGenerationTimeMs = 0.0f;

    int activeChunkCount = 0;
    int cameraChunkX = 0;
    int cameraChunkZ = 0;
};

