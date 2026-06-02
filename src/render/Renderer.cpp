//
// Created by Tharmiga Loganathan on 2026-05-26.
//

#include "Renderer.h"
#include "Camera.h"

#include <glad/gl.h>
#include <glm/mat4x4.hpp>
#include <vector>

namespace {
    std::vector<float> makeGridVertices(int halfSize) {
        // Generate line segments on the XZ plane. Each grid line contributes two vertices.
        //
        std::vector<float> vertices;

        for (int i = -halfSize; i <= halfSize; ++i) {
            // Line parallel to Z axis
            vertices.push_back(static_cast<float>(i));
            vertices.push_back(0.0f);
            vertices.push_back(static_cast<float>(-halfSize));

            vertices.push_back(static_cast<float>(i));
            vertices.push_back(0.0f);
            vertices.push_back(static_cast<float>(halfSize));

            // Line parallel to X axis
            vertices.push_back(static_cast<float>(-halfSize));
            vertices.push_back(0.0f);
            vertices.push_back(static_cast<float>(i));

            vertices.push_back(static_cast<float>(halfSize));
            vertices.push_back(0.0f);
            vertices.push_back(static_cast<float>(i));
        }

        return vertices;
    }
}

Renderer::Renderer()
    : basicShader("assets/shaders/basic.vert", "assets/shaders/basic.frag"),
      gridMesh(makeGridVertices(20), GL_LINES) {}

void Renderer::beginFrame() {
    // Tells OpenGL to use depth information so closer objects can appear in front of farther objects.
    //
    glEnable(GL_DEPTH_TEST);

    glClearColor(0.08f, 0.09f, 0.11f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::drawGrid(const Camera& camera) {
    basicShader.use();
    // Draw a temporary XZ-plane grid to validate the 3D camera and projection pipeline.
    //
    basicShader.setMat4("u_ViewProjection", camera.viewProjectionMatrix());
    basicShader.setMat4("u_Model", glm::mat4(1.0f));

    gridMesh.draw();
}

void Renderer::endFrame() {
    // STUB
}