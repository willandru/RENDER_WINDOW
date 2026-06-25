#include "Window.h"
#include "Renderer.h"
#include "Shader.h"

int main()
{
    Window window(
        1280,
        720,
        "RENDER_WINDOW"
    );

    Shader shader(
    "Debug/basic.vert",
    "Debug/basic.frag"
    );

    Renderer renderer;

    while (!window.shouldClose())
    {
        window.pollEvents();

        window.clear();

        renderer.draw(shader);

        window.display();
    }

    return 0;
}