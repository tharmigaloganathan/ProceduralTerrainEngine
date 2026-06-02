//
// Created by Tharmiga Loganathan on 2026-06-01.
//

#include "Input.h"

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

Input::Input(GLFWwindow* window)
    : window(window) {}

bool Input::isKeyDown(int key) const {
    return glfwGetKey(window, key) == GLFW_PRESS;
}