//
// Created by Tharmiga Loganathan on 2026-05-26.
//

#include "Window.h"

#include <glad/gl.h>
#include <GLFW/glfw3.h>

#include <stdexcept>

namespace {
    void framebufferSizeCallback(GLFWwindow* window, int width, int height) {
        glViewport(0, 0, width, height);
    }
}

Window::Window(int width, int height, const char* title) {
    if (!glfwInit()) {
        throw std::runtime_error("Failed to initialize GLFW");
    }

    // Request an OpenGL 3.3 Core Profile context.
    //
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    // macOS requires forward-compatible OpenGL when using the core profile.
    //
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    handle = glfwCreateWindow(width, height, title, nullptr, nullptr);
    if (!handle) {
        glfwTerminate();
        throw std::runtime_error("Failed to create GLFW window.");
    }

    // GLFW creates the native window and OpenGL context. OpenGL calls
    // are only valid after a context has been created and made current.
    //
    glfwMakeContextCurrent(handle);

    // GLAD loads the OpenGL function pointers for the current context.
    // This must happen after glfwMakeContextCurrent().
    //
    if (!gladLoadGL(glfwGetProcAddress)) {
        throw std::runtime_error("Failed to initialize GLAD");
    }

    // Use the framebuffer size, not the window size, so rendering works correctly
    // on high-DPI/Retina displays.
    //
    int framebufferWidth = 0;
    int framebufferHeight = 0;
    glfwGetFramebufferSize(handle, &framebufferWidth, &framebufferHeight);
    glViewport(0, 0, framebufferWidth, framebufferHeight);

    // Keep OpenGL's viewport in sync when the drawable framebuffer changes size.
    //
    glfwSetFramebufferSizeCallback(handle, framebufferSizeCallback);

}

// RAII cleanup: Window owns the GLFW window lifetime.
//
Window::~Window() {
    if (handle) {
        glfwWindowShouldClose(handle);
    }
    glfwTerminate();
}

bool Window::shouldClose() const {
    return glfwWindowShouldClose(handle);
}

void Window::pollEvents() {
    glfwPollEvents();
}

void Window::swapBuffers() {
    glfwSwapBuffers(handle);
}

int Window::framebufferWidth() const {
    int width = 0;
    int height = 0;
    glfwGetFramebufferSize(handle, &width, &height);
    return width;
}

int Window::framebufferHeight() const {
    int width = 0;
    int height = 0;
    glfwGetFramebufferSize(handle, &width, &height);
    return height;
}

GLFWwindow* Window::nativeHandle() const {
    return handle;
}