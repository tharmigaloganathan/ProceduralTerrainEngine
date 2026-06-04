//
// Created by Tharmiga Loganathan on 2026-06-01.
//

#include "Input.h"

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

Input::Input(GLFWwindow* window)
    : window(window) {}

void Input::update() {
    previousRDown = currentRDown;
    currentRDown = isKeyDown(GLFW_KEY_R);
}

bool Input::isKeyDown(int key) const {
    return glfwGetKey(window, key) == GLFW_PRESS;
}

bool Input::wasKeyPressed(int key) const {
    if (key == GLFW_KEY_R) {
        return currentRDown && !previousRDown;
    }

    return false;
}