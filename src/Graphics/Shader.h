#pragma once

#include <glad/glad.h>

class Shader
{
public:

    Shader();

    ~Shader();

    bool create(
        const char* vertexShaderPath,
        const char* fragmentShaderPath
    );

    void use() const;

    GLuint getProgram() const;

    void destroy();

private:

    GLuint m_program;
};