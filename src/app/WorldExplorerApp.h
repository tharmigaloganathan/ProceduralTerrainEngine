//
// Created by Tharmiga Loganathan on 2026-05-26.
//

#pragma once

#include "../input/Input.h"
#include "../platform/Window.h"
#include "../render/Camera.h"
#include "../render/Renderer.h"
#include "../world/TerrainGenerator.h"
#include "../core/PerformanceMetrics.h"
#include "../world/ChunkManager.h"
#include "../world/ChunkCoord.h"

class WorldExplorerApp {
public:
    WorldExplorerApp();
    void run();

private:
    void update(float deltaTime);
    void updateWindowTitle(float deltaTime);
    float aspectRatio() const;
    ChunkCoord currentCameraChunkCoord() const;

    // Construction order matters: Window creates the OpenGL context before Renderer creates GPU resources.
    //
    Window window;
    Input input;
    Camera camera;
    Renderer renderer;

    TerrainSettings terrainSettings;
    ChunkManager chunkManager;
    PerformanceMetrics metrics;

    float metricsTitleUpdateAccumulator = 0.0f;
};
