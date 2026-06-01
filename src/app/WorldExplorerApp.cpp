//
// Created by Tharmiga Loganathan on 2026-05-26.
//

#include "WorldExplorerApp.h"

WorldExplorerApp::WorldExplorerApp()
    : window(1280, 720, "Procedural World Explorer"),
      renderer() {}

void WorldExplorerApp::run() {
    // Main application loop: poll platform events, render one frame, then present it.
    //
    while (!window.shouldClose()) {
        window.pollEvents();

        renderer.beginFrame();
        renderer.drawTestTriangle();
        renderer.endFrame();

        window.swapBuffers();
    }
}