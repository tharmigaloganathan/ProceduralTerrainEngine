//
// Created by Tharmiga Loganathan on 2026-06-01.
//

#pragma once

#include <string>
#include <glm/mat4x4.hpp>

class Shader {
public:
    Shader(const std::string& vertexPath, const std::string& fragmentPath);
    ~Shader();

    Shader(const Shader&) = delete;
    Shader& operator=(const Shader&) = delete;

    Shader(Shader&& other) noexcept;
    Shader& operator=(Shader&& other) noexcept;

    void use() const;
    void setMat4(const std::string& name, const glm::mat4& matrix) const;

private:
    // OpenGL shader program owned by this wrapper.
    //
    unsigned int programId = 0;

    static std::string readFile(const std::string& path);
    static unsigned int compileShader(unsigned int type, const std::string& source);
};
