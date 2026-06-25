#pragma once

struct GLFWwindow;

class Window
{
public:

    Window();

    ~Window();

    bool create(
        int width,
        int height,
        const char* title
    );

    bool shouldClose() const;

    void pollEvents();

    void swapBuffers();

    void destroy();

    GLFWwindow* getNativeWindow() const;

private:

    GLFWwindow* m_window;
};