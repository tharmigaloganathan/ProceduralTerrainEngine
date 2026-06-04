//
// Created by Tharmiga Loganathan on 2026-05-26.
//

#pragma once

#include <string>

struct GLFWwindow;

class Window {
    public:
        Window(int width, int height, const char* title);
        ~Window();

        Window(const Window&) = delete;
        Window& operator=(const Window&) = delete;

        bool shouldClose() const;
        void pollEvents();
        void swapBuffers();

        int framebufferWidth() const;
        int framebufferHeight() const;

        GLFWwindow* nativeHandle() const;

        // Update the native window title; used for temporary debug metrics display.
        //
        void setTitle(const std::string& title) const;

    private:
        // Window owns the GLFW window handle and releases it in the destructor.
        //
        GLFWwindow* handle = nullptr;
};
