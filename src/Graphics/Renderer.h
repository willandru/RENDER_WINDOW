#pragma once

#include <glad/glad.h>

class Renderer
{
public:

    Renderer();

    ~Renderer();

    bool create();

    void destroy();

    void clear(
        float r,
        float g,
        float b
    );

    void drawRectangle(
        GLuint shaderProgram,
        float x,
        float y,
        float width,
        float height,
        int windowWidth,
        int windowHeight,
        float r,
        float g,
        float b
    );

private:

    GLuint m_vao;
    GLuint m_vbo;
};