#include "Window.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

Window::Window(int width, int height, const char* title)
    : m_window(nullptr)
{
    if (!glfwInit())
    {
        std::cerr << "ERROR: glfwInit() failed\n";
        return;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    m_window = glfwCreateWindow(width, height, title, nullptr, nullptr);

    if (!m_window)
    {
        std::cerr << "ERROR: glfwCreateWindow() failed\n";
        glfwTerminate();
        return;
    }

    glfwMakeContextCurrent(m_window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cerr << "ERROR: gladLoadGLLoader() failed\n";
        glfwDestroyWindow(m_window);
        glfwTerminate();
        m_window = nullptr;
        return;
    }

    glViewport(0, 0, width, height);
}

Window::~Window()
{
    if (m_window)
    {
        glfwDestroyWindow(m_window);
    }

    glfwTerminate();
}

bool Window::shouldClose() const
{
    return !m_window || glfwWindowShouldClose(m_window);
}

void Window::pollEvents()
{
    glfwPollEvents();
}

void Window::clear()
{
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

void Window::display()
{
    glfwSwapBuffers(m_window);
}