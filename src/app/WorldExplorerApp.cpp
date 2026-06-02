//
// Created by Tharmiga Loganathan on 2026-05-26.
//

#include "WorldExplorerApp.h"

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

WorldExplorerApp::WorldExplorerApp()
    : window(1280, 720, "Procedural Terrain Engine"),
      input(window.nativeHandle()),
      camera(aspectRatio()),
      renderer() {}

void WorldExplorerApp::run() {
    float lastTime = static_cast<float>(glfwGetTime());

    // Main application loop: poll platform events, render one frame, then present it.
    //
    while (!window.shouldClose()) {
        const float currentTime = static_cast<float>(glfwGetTime());
        const float deltaTime = currentTime - lastTime;
        lastTime = currentTime;

        window.pollEvents();

        update(deltaTime);

        renderer.beginFrame();
        renderer.drawScene(camera);
        renderer.endFrame();

        window.swapBuffers();
    }
}

void WorldExplorerApp::update(float deltaTime) {
    camera.setAspectRatio(aspectRatio());

    const float moveSpeed = 5.0f;
    const float rotateSpeed = 75.0f;

    // Scale movement by delta time so camera speed is inpdendent of frame rate.
    //
    const float moveAmount = moveSpeed * deltaTime;
    const float rotateAmount = rotateSpeed * deltaTime;

    if (input.isKeyDown(GLFW_KEY_W)) {
        camera.moveForward(moveAmount);
    }

    if (input.isKeyDown(GLFW_KEY_S)) {
        camera.moveForward(-moveAmount);
    }

    if (input.isKeyDown(GLFW_KEY_D)) {
        camera.moveRight(moveAmount);
    }

    if (input.isKeyDown(GLFW_KEY_A)) {
        camera.moveRight(-moveAmount);
    }

    if (input.isKeyDown(GLFW_KEY_E)) {
        camera.moveUp(moveAmount);
    }

    if (input.isKeyDown(GLFW_KEY_Q)) {
        camera.moveUp(-moveAmount);
    }

    if (input.isKeyDown(GLFW_KEY_LEFT)) {
        camera.rotate(-rotateAmount, 0.0f);
    }

    if (input.isKeyDown(GLFW_KEY_RIGHT)) {
        camera.rotate(rotateAmount, 0.0f);
    }

    if (input.isKeyDown(GLFW_KEY_UP)) {
        camera.rotate(0.0f, rotateAmount);
    }

    if (input.isKeyDown(GLFW_KEY_DOWN)) {
        camera.rotate(0.0f, -rotateAmount);
    }
}

float WorldExplorerApp::aspectRatio() const {
    const int width = window.framebufferWidth();
    const int height = window.framebufferHeight();

    // Avoid division by zero while the window is minimized or resizing.
    //
    if (height == 0) {
        return 1.0f;
    }

    return static_cast<float>(width) / static_cast<float>(height);
}