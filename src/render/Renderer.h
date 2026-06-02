//
// Created by Tharmiga Loganathan on 2026-05-26.
//

#pragma once

#include "Shader.h"
#include "Mesh.h"
#include "world/TerrainGenerator.h"

class Camera;

class Renderer {
public:
    Renderer();

    void beginFrame();
    void drawScene(const Camera& camera);
    void endFrame();

private:
    Shader basicShader;
    Mesh terrainMesh;
};

