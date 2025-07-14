cmake_minimum_required(VERSION 3.10)
project(OpenGLProject VERSION 1.0)
cmake_policy(SET CMP0072 NEW)

find_package(OpenGL REQUIRED)

add_executable(MyOGPropject 
    src/main.cpp
    src/glad.h
    src/glad.c
)

target_link_libraries(MyOGPropject 
    glfw
    OpenGL::GL
)