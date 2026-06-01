//
// Created by Tharmiga Loganathan on 2026-06-01.
//

#include "Shader.h"

#include <glad/gl.h>

#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>

Shader::Shader(const std::string& vertexPath, const std::string& fragmentPath) {
    // Read GLSL source from disk so shaders can be edited without recompiling C++.
    //
    const std::string vertexSource = readFile(vertexPath);
    const std::string fragmentSource = readFile(fragmentPath);

    // Compile vertex and fragment shaders separately, then link them into one GPU program.
    //
    const unsigned int vertexShader = compileShader(GL_VERTEX_SHADER, vertexSource);
    const unsigned int fragmentShader = compileShader(GL_FRAGMENT_SHADER, fragmentSource);

    programId = glCreateProgram();
    glAttachShader(programId, vertexShader);
    glAttachShader(programId, fragmentShader);
    glLinkProgram(programId);

    int success = 0;
    glGetProgramiv(programId, GL_LINK_STATUS, &success);

    if (!success) {
        char infoLog[1024];
        glGetProgramInfoLog(programId, 1024, nullptr, infoLog);

        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
        glDeleteProgram(programId);
        programId = 0;

        throw std::runtime_error(std::string("Shader program link failed:\n") + infoLog);
    }

    // Individual shader objects are no longer needed after linking.
    //
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

// RAII cleanup: Shader owns the OpenGL program object.
//
Shader::~Shader() {
    if (programId != 0) {
        glDeleteProgram(programId);
    }
}

// Move ownership of the OpenGL program without deleting it from the source object.
//
Shader::Shader(Shader&& other) noexcept
    : programId(other.programId) {
      other.programId = 0;
}

Shader& Shader::operator=(Shader&& other) noexcept {
    if (this != &other) {
        if (programId != 0) {
            glDeleteProgram(programId);
        }

        programId = other.programId;
        other.programId = 0;
    }

    return *this;
}

void Shader::use() const {
    glUseProgram(programId);
}

std::string Shader::readFile(const std::string& path) {
    std::ifstream file(path);

    if (!file.is_open()) {
        throw std::runtime_error("Failed to open shader file: " + path);
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

unsigned int Shader::compileShader(unsigned int type, const std::string& source) {
    const unsigned int shader = glCreateShader(type);

    const char* sourceCStr = source.c_str();
    glShaderSource(shader, 1, &sourceCStr, nullptr);
    glCompileShader(shader);

    int success = 0;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

    if (!success) {
        char infoLog[1024];
        glGetShaderInfoLog(shader, 1024, nullptr, infoLog);

        glDeleteShader(shader);

        const std::string shaderType = type == GL_VERTEX_SHADER ? "vertex" : "fragment";
        throw std::runtime_error(shaderType + " shader compilation failed:\n" + infoLog);
    }

    return shader;
}