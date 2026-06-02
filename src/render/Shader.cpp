//
// Created by Tharmiga Loganathan on 2026-06-01.
//

#include "Shader.h"

#include <glad/gl.h>
#include <glm/gtc/type_ptr.hpp>

#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>

Shader::Shader(const std::string& vertexPath, const std::string& fragmentPath) {
    // Read GLSL source from disk so shaders can be edited without recompiling C++.
    //
    const std::string vertexSource = readFile(vertexPath);
    const std::string fragmentSource = readFile(fragmentPath);

    // Vertex and fragment shaders are compiled separately, then linked into one program.
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

    // Individual shader objects are no longer needed once the program is linked.
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
        // Release the currently owned program before taking ownership of another.
        //
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

void Shader::setMat4(const std::string& name, const glm::mat4& matrix) const {
    // Send a GLM matrix to the matching GLSL uniform.
    //
    const int location = glGetUniformLocation(programId, name.c_str());
    glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
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