#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

enum class Screen
{
    MainMenu,
    OneVsAI,
    OneMatch,
    Match
};

struct Button
{
    float x;
    float y;
    float width;
    float height;
};

static Screen currentScreen = Screen::MainMenu;

GLuint createShaderProgram()
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

    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

    glShaderSource(
        vertexShader,
        1,
        &vertexShaderSource,
        nullptr
    );

    glCompileShader(vertexShader);

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

        return 0;
    }

    GLuint fragmentShader =
        glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(
        fragmentShader,
        1,
        &fragmentShaderSource,
        nullptr
    );

    glCompileShader(fragmentShader);

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

        return 0;
    }

    GLuint program = glCreateProgram();

    glAttachShader(
        program,
        vertexShader
    );

    glAttachShader(
        program,
        fragmentShader
    );

    glLinkProgram(program);

    glGetProgramiv(
        program,
        GL_LINK_STATUS,
        &success
    );

    if (!success)
    {
        char infoLog[512];

        glGetProgramInfoLog(
            program,
            sizeof(infoLog),
            nullptr,
            infoLog
        );

        std::cerr
            << "Program link error:\n"
            << infoLog
            << '\n';

        return 0;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return program;
}

bool isInsideButton(
    const Button& button,
    double mouseX,
    double mouseY)
{
    return
        mouseX >= button.x &&
        mouseX <= button.x + button.width &&
        mouseY >= button.y &&
        mouseY <= button.y + button.height;
}

void drawRectangle(
    GLuint vao,
    GLuint vbo,
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

    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    glBufferSubData(
        GL_ARRAY_BUFFER,
        0,
        sizeof(vertices),
        vertices
    );

    glUseProgram(shaderProgram);

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

    glBindVertexArray(vao);

    glDrawArrays(
        GL_TRIANGLES,
        0,
        6
    );
}

int main()
{
    if (!glfwInit())
    {
        std::cerr
            << "GLFW initialization failed\n";

        return -1;
    }

    glfwWindowHint(
        GLFW_CONTEXT_VERSION_MAJOR,
        3
    );

    glfwWindowHint(
        GLFW_CONTEXT_VERSION_MINOR,
        3
    );

    glfwWindowHint(
        GLFW_OPENGL_PROFILE,
        GLFW_OPENGL_CORE_PROFILE
    );

    GLFWwindow* window =
        glfwCreateWindow(
            1280,
            720,
            "RENDER_WINDOW",
            nullptr,
            nullptr
        );

    if (!window)
    {
        std::cerr
            << "Window creation failed\n";

        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader(
        (GLADloadproc)glfwGetProcAddress))
    {
        std::cerr
            << "GLAD initialization failed\n";

        glfwDestroyWindow(window);
        glfwTerminate();

        return -1;
    }

    GLuint shaderProgram =
        createShaderProgram();

    if (shaderProgram == 0)
    {
        glfwDestroyWindow(window);
        glfwTerminate();

        return -1;
    }

    GLuint vao = 0;
    GLuint vbo = 0;

    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);

    glBindVertexArray(vao);

    glBindBuffer(
        GL_ARRAY_BUFFER,
        vbo
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

    glEnableVertexAttribArray(0);

    Button oneVsAI =
    {
        490.0f,
        150.0f,
        300.0f,
        70.0f
    };

    Button oneMatch =
    {
        490.0f,
        260.0f,
        300.0f,
        70.0f
    };

    Button match =
    {
        490.0f,
        370.0f,
        300.0f,
        70.0f
    };

    Button exitButton =
    {
        490.0f,
        480.0f,
        300.0f,
        70.0f
    };

    Button backButton =
    {
        50.0f,
        50.0f,
        200.0f,
        60.0f
    };

    bool previousMouseState = false;

    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

        int width;
        int height;

        glfwGetFramebufferSize(
            window,
            &width,
            &height
        );

        glViewport(
            0,
            0,
            width,
            height
        );

        double mouseX;
        double mouseY;

        glfwGetCursorPos(
            window,
            &mouseX,
            &mouseY
        );

        bool mousePressed =
            glfwGetMouseButton(
                window,
                GLFW_MOUSE_BUTTON_LEFT
            ) == GLFW_PRESS;

        bool clicked =
            mousePressed &&
            !previousMouseState;

        previousMouseState =
            mousePressed;

        if (currentScreen ==
            Screen::MainMenu)
        {
            if (clicked)
            {
                if (isInsideButton(
                    oneVsAI,
                    mouseX,
                    mouseY))
                {
                    currentScreen =
                        Screen::OneVsAI;
                }
                else if (isInsideButton(
                    oneMatch,
                    mouseX,
                    mouseY))
                {
                    currentScreen =
                        Screen::OneMatch;
                }
                else if (isInsideButton(
                    match,
                    mouseX,
                    mouseY))
                {
                    currentScreen =
                        Screen::Match;
                }
                else if (isInsideButton(
                    exitButton,
                    mouseX,
                    mouseY))
                {
                    glfwSetWindowShouldClose(
                        window,
                        GLFW_TRUE
                    );
                }
            }

            glClearColor(
                0.08f,
                0.08f,
                0.12f,
                1.0f
            );

            glClear(GL_COLOR_BUFFER_BIT);

            drawRectangle(
                vao,
                vbo,
                shaderProgram,
                oneVsAI.x,
                oneVsAI.y,
                oneVsAI.width,
                oneVsAI.height,
                width,
                height,
                0.2f,
                0.6f,
                0.9f
            );

            drawRectangle(
                vao,
                vbo,
                shaderProgram,
                oneMatch.x,
                oneMatch.y,
                oneMatch.width,
                oneMatch.height,
                width,
                height,
                0.2f,
                0.8f,
                0.4f
            );

            drawRectangle(
                vao,
                vbo,
                shaderProgram,
                match.x,
                match.y,
                match.width,
                match.height,
                width,
                height,
                0.9f,
                0.6f,
                0.2f
            );

            drawRectangle(
                vao,
                vbo,
                shaderProgram,
                exitButton.x,
                exitButton.y,
                exitButton.width,
                exitButton.height,
                width,
                height,
                0.8f,
                0.2f,
                0.2f
            );
        }
        else
        {
            if (clicked)
            {
                if (isInsideButton(
                    backButton,
                    mouseX,
                    mouseY))
                {
                    currentScreen =
                        Screen::MainMenu;
                }
            }

            if (currentScreen ==
                Screen::OneVsAI)
            {
                glClearColor(
                    0.1f,
                    0.2f,
                    0.5f,
                    1.0f
                );
            }
            else if (currentScreen ==
                     Screen::OneMatch)
            {
                glClearColor(
                    0.2f,
                    0.5f,
                    0.2f,
                    1.0f
                );
            }
            else
            {
                glClearColor(
                    0.5f,
                    0.2f,
                    0.2f,
                    1.0f
                );
            }

            glClear(GL_COLOR_BUFFER_BIT);

            drawRectangle(
                vao,
                vbo,
                shaderProgram,
                backButton.x,
                backButton.y,
                backButton.width,
                backButton.height,
                width,
                height,
                0.9f,
                0.9f,
                0.9f
            );
        }

        glfwSwapBuffers(window);
    }

    glDeleteBuffers(
        1,
        &vbo
    );

    glDeleteVertexArrays(
        1,
        &vao
    );

    glDeleteProgram(
        shaderProgram
    );

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}