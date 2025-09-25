cmake_minimum_required(VERSION 3.10)
project(OpenGLProject VERSION 1.0)
cmake_policy(SET CMP0072 NEW)

find_package(OpenGL REQUIRED)

# Add include directories
include_directories(
    ${CMAKE_SOURCE_DIR}/src/HeaderFiles
    ${CMAKE_SOURCE_DIR}/src/Shaders
    ${CMAKE_SOURCE_DIR}/src
)

add_definitions(-DSHADER_DIR="${CMAKE_SOURCE_DIR}/src/Shaders/")

file(COPY ${CMAKE_SOURCE_DIR}/src/Shaders/ DESTINATION ${CMAKE_BINARY_DIR}/Shaders)

add_executable(MyOGPropject 
    src/main.cpp
    src/glad.h
    src/glad.c
    src/EBO.cpp
    src/VAO.cpp
    src/VBO.cpp
    src/shaderClass.cpp
    src/stb_image.cpp
)

target_link_libraries(MyOGPropject 
    glfw
    OpenGL::GL
)