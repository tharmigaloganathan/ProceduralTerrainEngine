//
// Created by Tharmiga Loganathan on 2026-06-01.
//

#ifndef PROCEDURALTERRAINENGINE_SHADER_H
#define PROCEDURALTERRAINENGINE_SHADER_H

#pragma once

#include <string>

class Shader {
public:
    Shader(const std::string& vertexPath, const std::string& fragmentPath);
    ~Shader();

    Shader(const Shader&) = delete;
    Shader& operator=(const Shader&) = delete;

    Shader(Shader&& other) noexcept;
    Shader& operator=(Shader&& other) noexcept;

    void use() const;

private:
    unsigned int programId = 0;

    static std::string readFile(const std::string& path);
    static unsigned int compileShader(unsigned int type, const std::string& source);
};


#endif //PROCEDURALTERRAINENGINE_SHADER_H
