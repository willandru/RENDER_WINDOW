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
)

target_include_directories(RENDER_WINDOW PRIVATE
    externals/glad/include
    externals/glfw-3.4/include
    externals/glm
)

target_link_libraries(RENDER_WINDOW PRIVATE
    glad
    glfw
)

if(WIN32)
    target_link_libraries(RENDER_WINDOW PRIVATE opengl32)
endif()