//
// Created by Tharmiga Loganathan on 2026-05-26.
//

#include "Renderer.h"
#include "Camera.h"

#include <glad/gl.h>
#include <glm/mat4x4.hpp>

namespace {
    // Converts CPU-generated terrain data into a GPU mesh.
    //
    std::unique_ptr<Mesh> createTerrainMesh(const TerrainSettings& settings) {
        TerrainGenerator generator;
        TerrainMeshData terrainData = generator.generate(settings);

        return std::make_unique<Mesh>(
            terrainData.vertices,
            terrainData.indices,
            GL_TRIANGLES
            );
    }
}

Renderer::Renderer()
    : basicShader("assets/shaders/basic.vert", "assets/shaders/basic.frag"),
      terrainMesh(createTerrainMesh(TerrainSettings{})) {}

void Renderer::beginFrame() {
    // Tells OpenGL to use depth information so closer objects can appear in front of farther objects.
    //
    glEnable(GL_DEPTH_TEST);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    // glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    glClearColor(0.08f, 0.09f, 0.11f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::drawScene(const Camera& camera) {
    basicShader.use();
    // Draw a temporary XZ-plane grid to validate the 3D camera and projection pipeline.
    //
    basicShader.setMat4("u_ViewProjection", camera.viewProjectionMatrix());
    basicShader.setMat4("u_Model", glm::mat4(1.0f));

    if (terrainMesh != nullptr) {
        terrainMesh->draw();
    }
}

void Renderer::endFrame() {
    // STUB
}

// Replaces the active terrain mesh; the old mesh releases its GPU buffers through RAII.
//
void Renderer::regenerateTerrain(const TerrainSettings& settings) {
    terrainMesh = createTerrainMesh(settings);
}