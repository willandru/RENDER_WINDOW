#pragma once

class Shader;

class Renderer
{
public:
    Renderer();
    ~Renderer();

    void draw(const Shader& shader);

private:
    unsigned int m_vao;
    unsigned int m_vbo;
    unsigned int m_ebo;
};