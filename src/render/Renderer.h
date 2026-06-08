//
// Created by Tharmiga Loganathan on 2026-05-26.
//

#pragma once

#include "Shader.h"
#include "world/Chunk.h"

#include <vector>

class Camera;

class Renderer {
public:
    Renderer();

    void beginFrame();
    void drawScene(const Camera& camera, const std::vector<const Chunk*>& chunks);
    void endFrame();

private:
    Shader basicShader;

};

