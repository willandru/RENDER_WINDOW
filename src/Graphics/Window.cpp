#include "Window.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

Window::Window()
    : m_window(nullptr)
{
}

Window::~Window()
{
    destroy();
}

bool Window::create(
    int width,
    int height,
    const char* title)
{
    if (!glfwInit())
    {
        std::cerr
            << "GLFW initialization failed\n";

        return false;
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

    m_window =
        glfwCreateWindow(
            width,
            height,
            title,
            nullptr,
            nullptr
        );

    if (!m_window)
    {
        std::cerr
            << "Window creation failed\n";

        glfwTerminate();

        return false;
    }

    glfwMakeContextCurrent(
        m_window
    );

    if (!gladLoadGLLoader(
        (GLADloadproc)
        glfwGetProcAddress))
    {
        std::cerr
            << "GLAD initialization failed\n";

        glfwDestroyWindow(
            m_window
        );

        glfwTerminate();

        m_window = nullptr;

        return false;
    }

    return true;
}

bool Window::shouldClose() const
{
    return glfwWindowShouldClose(
        m_window
    );
}

void Window::pollEvents()
{
    glfwPollEvents();
}

void Window::swapBuffers()
{
    glfwSwapBuffers(
        m_window
    );
}

void Window::destroy()
{
    if (m_window)
    {
        glfwDestroyWindow(
            m_window
        );

        m_window = nullptr;
    }

    glfwTerminate();
}

GLFWwindow* Window::getNativeWindow() const
{
    return m_window;
}