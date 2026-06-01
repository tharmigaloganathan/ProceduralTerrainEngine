//
// Created by Tharmiga Loganathan on 2026-05-26.
//

#ifndef PROCEDURALTERRAINENGINE_WORLDEXPLORERAPP_H
#define PROCEDURALTERRAINENGINE_WORLDEXPLORERAPP_H

#pragma once

#include "../platform/Window.h"
#include "../render/Renderer.h"

class WorldExplorerApp {
public:
    WorldExplorerApp();
    void run();

private:
    // Construction order matters: Window creates the OpenGL context before Renderer creates GPU resources.
    //
    Window window;
    Renderer renderer;
};


#endif //PROCEDURALTERRAINENGINE_WORLDEXPLORERAPP_H
