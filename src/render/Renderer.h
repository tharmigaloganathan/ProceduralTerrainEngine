//
// Created by Tharmiga Loganathan on 2026-05-26.
//

#ifndef PROCEDURALTERRAINENGINE_RENDERER_H
#define PROCEDURALTERRAINENGINE_RENDERER_H

#pragma once

#include "Shader.h"
#include "Mesh.h"

class Renderer {
public:
    Renderer();

    void beginFrame();
    void drawTestTriangle();
    void endFrame();

private:
    Shader basicShader;
    Mesh triangleMesh;
};


#endif //PROCEDURALTERRAINENGINE_RENDERER_H
