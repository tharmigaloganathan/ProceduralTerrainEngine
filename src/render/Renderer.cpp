//
// Created by Tharmiga Loganathan on 2026-05-26.
//

#include "Renderer.h"

#include <glad/gl.h>
#include <vector>

Renderer::Renderer()
    : basicShader("assets/shaders/basic.vert", "assets/shaders/basic.frag"),
      triangleMesh(std::vector<float>{  // Temporary Day 1 geometry used to validate the rendering pipeline.
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.0f,  0.5f, 0.0f
      }) {}

void Renderer::beginFrame() {
    // Clear the frame before drawing. Later this will also enable depth testing for 3D terrain.
    //
    glClearColor(0.08f, 0.09f, 0.11f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

void Renderer::drawTestTriangle() {
    // Bind the shader and draw the test mesh.
    //
    basicShader.use();
    triangleMesh.draw();
}

void Renderer::endFrame() {
    // STUB
}