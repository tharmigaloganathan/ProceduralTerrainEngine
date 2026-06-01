//
// Created by Tharmiga Loganathan on 2026-05-26.
//

#ifndef PROCEDURALTERRAINENGINE_WINDOW_H
#define PROCEDURALTERRAINENGINE_WINDOW_H

#pragma once

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

    private:
        GLFWwindow* handle = nullptr;
};


#endif //PROCEDURALTERRAINENGINE_WINDOW_H
