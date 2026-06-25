#include "Renderer.h"

Renderer::Renderer()
    : m_vao(0),
      m_vbo(0)
{
}

Renderer::~Renderer()
{
    destroy();
}

bool Renderer::create()
{
    glGenVertexArrays(
        1,
        &m_vao
    );

    glGenBuffers(
        1,
        &m_vbo
    );

    glBindVertexArray(
        m_vao
    );

    glBindBuffer(
        GL_ARRAY_BUFFER,
        m_vbo
    );

    glBufferData(
        GL_ARRAY_BUFFER,
        sizeof(float) * 12,
        nullptr,
        GL_DYNAMIC_DRAW
    );

    glVertexAttribPointer(
        0,
        2,
        GL_FLOAT,
        GL_FALSE,
        2 * sizeof(float),
        nullptr
    );

    glEnableVertexAttribArray(
        0
    );

    return true;
}

void Renderer::destroy()
{
    if (m_vbo)
    {
        glDeleteBuffers(
            1,
            &m_vbo
        );

        m_vbo = 0;
    }

    if (m_vao)
    {
        glDeleteVertexArrays(
            1,
            &m_vao
        );

        m_vao = 0;
    }
}

void Renderer::drawRectangle(
    GLuint shaderProgram,
    float x,
    float y,
    float width,
    float height,
    int windowWidth,
    int windowHeight,
    float r,
    float g,
    float b)
{
    float left =
        (x / windowWidth) * 2.0f - 1.0f;

    float right =
        ((x + width) / windowWidth) * 2.0f - 1.0f;

    float top =
        1.0f - (y / windowHeight) * 2.0f;

    float bottom =
        1.0f - ((y + height) / windowHeight) * 2.0f;

    float vertices[] =
    {
        left,  top,
        right, top,
        right, bottom,

        left,  top,
        right, bottom,
        left,  bottom
    };

    glBindBuffer(
        GL_ARRAY_BUFFER,
        m_vbo
    );

    glBufferSubData(
        GL_ARRAY_BUFFER,
        0,
        sizeof(vertices),
        vertices
    );

    glUseProgram(
        shaderProgram
    );

    GLint colorLocation =
        glGetUniformLocation(
            shaderProgram,
            "uColor"
        );

    glUniform3f(
        colorLocation,
        r,
        g,
        b
    );

    glBindVertexArray(
        m_vao
    );

    glDrawArrays(
        GL_TRIANGLES,
        0,
        6
    );
}