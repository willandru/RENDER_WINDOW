#include "Shader.h"

#include <iostream>

Shader::Shader()
    : m_program(0)
{
}

Shader::~Shader()
{
    destroy();
}

bool Shader::create()
{
    const char* vertexShaderSource = R"(
        #version 330 core

        layout(location = 0) in vec2 aPos;

        void main()
        {
            gl_Position = vec4(aPos, 0.0, 1.0);
        }
    )";

    const char* fragmentShaderSource = R"(
        #version 330 core

        out vec4 FragColor;

        uniform vec3 uColor;

        void main()
        {
            FragColor = vec4(uColor, 1.0);
        }
    )";

    GLuint vertexShader =
        glCreateShader(GL_VERTEX_SHADER);

    glShaderSource(
        vertexShader,
        1,
        &vertexShaderSource,
        nullptr
    );

    glCompileShader(
        vertexShader
    );

    GLint success = 0;

    glGetShaderiv(
        vertexShader,
        GL_COMPILE_STATUS,
        &success
    );

    if (!success)
    {
        char infoLog[512];

        glGetShaderInfoLog(
            vertexShader,
            sizeof(infoLog),
            nullptr,
            infoLog
        );

        std::cerr
            << "Vertex shader error:\n"
            << infoLog
            << '\n';

        return false;
    }

    GLuint fragmentShader =
        glCreateShader(
            GL_FRAGMENT_SHADER
        );

    glShaderSource(
        fragmentShader,
        1,
        &fragmentShaderSource,
        nullptr
    );

    glCompileShader(
        fragmentShader
    );

    glGetShaderiv(
        fragmentShader,
        GL_COMPILE_STATUS,
        &success
    );

    if (!success)
    {
        char infoLog[512];

        glGetShaderInfoLog(
            fragmentShader,
            sizeof(infoLog),
            nullptr,
            infoLog
        );

        std::cerr
            << "Fragment shader error:\n"
            << infoLog
            << '\n';

        return false;
    }

    m_program =
        glCreateProgram();

    glAttachShader(
        m_program,
        vertexShader
    );

    glAttachShader(
        m_program,
        fragmentShader
    );

    glLinkProgram(
        m_program
    );

    glGetProgramiv(
        m_program,
        GL_LINK_STATUS,
        &success
    );

    if (!success)
    {
        char infoLog[512];

        glGetProgramInfoLog(
            m_program,
            sizeof(infoLog),
            nullptr,
            infoLog
        );

        std::cerr
            << "Program link error:\n"
            << infoLog
            << '\n';

        return false;
    }

    glDeleteShader(
        vertexShader
    );

    glDeleteShader(
        fragmentShader
    );

    return true;
}

void Shader::use() const
{
    glUseProgram(
        m_program
    );
}

GLuint Shader::getProgram() const
{
    return m_program;
}

void Shader::destroy()
{
    if (m_program)
    {
        glDeleteProgram(
            m_program
        );

        m_program = 0;
    }
}