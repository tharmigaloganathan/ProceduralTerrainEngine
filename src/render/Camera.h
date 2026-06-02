//
// Created by Tharmiga Loganathan on 2026-06-01.
//

#pragma once

#include <glm/glm.hpp>
#include <glm/mat4x4.hpp>

class Camera {
public:
    Camera(float aspectRatio);

    void moveForward(float amount);
    void moveRight(float amount);
    void moveUp(float amount);

    void rotate(float yawDelta, float pitchDelta);

    void setAspectRatio(float aspectRatio);

    glm::mat4 viewMatrix() const;
    glm::mat4 projectionMatrix() const;
    glm::mat4 viewProjectionMatrix() const;

    glm::vec3 position() const;

private:
    // Camera starts above and behind the grid, looking slightly downward.
    //
    glm::vec3 cameraPosition{0.0f, 2.0f, 5.0f};

    float yaw = -90.0f;
    float pitch = -20.0f;

    float fovDegrees = 60.0f;
    float aspectRatio = 16.0f / 9.0f;
    float nearPlane = 0.1f;
    float farPlane = 500.0f;

    glm::vec3 forward() const;
    glm::vec3 right() const;
};

