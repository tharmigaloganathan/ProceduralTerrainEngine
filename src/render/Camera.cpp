//
// Created by Tharmiga Loganathan on 2026-06-01.
//

#include "Camera.h"

#include <algorithm>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/trigonometric.hpp>

Camera::Camera(float aspectRatio)
    : aspectRatio(aspectRatio) {}

void Camera::moveForward(float amount) {
    cameraPosition += forward() * amount;
}

void Camera::moveRight(float amount) {
    cameraPosition += right() * amount;
}

void Camera::moveUp(float amount) {
    cameraPosition.y += amount;
}

void Camera::rotate(float yawDelta, float pitchDelta) {
    yaw += yawDelta;
    pitch += pitchDelta;

    // Prevent the camera from flipping when looking straight up/down.
    //
    pitch = std::clamp(pitch, -89.0f, 89.0f);
}

void Camera::setAspectRatio(float newAspectRatio) {
    aspectRatio = newAspectRatio;
}

// Build a view matrix from the camera position and direction.
//
glm::mat4 Camera::viewMatrix() const {
    return glm::lookAt(
        cameraPosition,
        cameraPosition + forward(),
        glm::vec3(0.0f, 1.0f, 0.0f)
        );
}

// Perspective projection preserves aspect ratio and creates depth.
//
glm::mat4 Camera::projectionMatrix() const {
    return glm::perspective(
        glm::radians(fovDegrees),
        aspectRatio,
        nearPlane,
        farPlane
        );
}

glm::mat4 Camera::viewProjectionMatrix() const {
    return projectionMatrix() * viewMatrix();
}

glm::vec3 Camera::position() const {
    return cameraPosition;
}

glm::vec3 Camera::forward() const {
    const float yawRadians = glm::radians(yaw);
    const float pitchRadians = glm::radians(pitch);

    glm::vec3 direction;
    direction.x = cos(yawRadians) * cos(pitchRadians);
    direction.y = sin(pitchRadians);
    direction.z = sin(yawRadians) * cos(pitchRadians);

    return glm::normalize(direction);
}

glm::vec3 Camera::right() const {
    return glm::normalize(glm::cross(forward(), glm::vec3(0.0f, 1.0f, 0.0f)));
}