//
// Created by Tharmiga Loganathan on 2026-06-01.
//

#pragma once

struct GLFWwindow;

class Input {
public:
    explicit Input(GLFWwindow* window);

    bool isKeyDown(int key) const;

private:
    // Non-owning pointer; Window owns the actual GLFWwindow.
    //
    GLFWwindow* window = nullptr;
};
