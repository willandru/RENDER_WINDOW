cmake_minimum_required(VERSION 3.20)

project(RENDER_WINDOW)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(externals/glfw-3.4)

add_library(glad
    externals/glad/src/glad.c
)

target_include_directories(glad PUBLIC
    externals/glad/include
)

add_executable(RENDER_WINDOW
    main.cpp

    src/Graphics/Window.cpp
    src/Graphics/Renderer.cpp
    src/Graphics/Shader.cpp
)

target_include_directories(RENDER_WINDOW PRIVATE
    src
    src/Graphics

    externals/glad/include
    externals/glfw-3.4/include
    externals/glm
)

target_link_libraries(RENDER_WINDOW PRIVATE
    glad
    glfw
)

if(WIN32)
    target_link_libraries(RENDER_WINDOW PRIVATE
        opengl32
    )
endif()

add_custom_command(
    TARGET RENDER_WINDOW POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${CMAKE_SOURCE_DIR}/src/Graphics/Shaders/basic.vert
        $<TARGET_FILE_DIR:RENDER_WINDOW>/basic.vert
)

add_custom_command(
    TARGET RENDER_WINDOW POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${CMAKE_SOURCE_DIR}/src/Graphics/Shaders/basic.frag
        $<TARGET_FILE_DIR:RENDER_WINDOW>/basic.frag
)