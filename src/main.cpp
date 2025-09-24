#include <iostream>
#include "glad.h"
#include <GLFW/glfw3.h>
#include <cmath>

#include "shaderClass.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"

// can use normal floats but safer to use GLfloats
GLfloat vertices[] = {
    -0.5f, -0.5f, 0.0f, // 0 bottom left
    0.5f, -0.5f, 0.0f, // 1 bottom right
    0.0f,  0.5f, 0.0f, // 2 top
    -0.25f, 0.0f, 0.0f, // 3 inner left
    0.25f, 0.0f, 0.0f, // 4 inner right
    0.0f, -0.5f, 0.0f // 5 inner bottom
};

GLuint indices[] = {
    0, 3, 5, // lower left triangle
    3, 2, 4, // upper triangle
    5, 4, 1 // lower right triangle
};

const int SCREEN_WIDTH = 1000;
const int SCREEN_HEIGHT = 800;

int main(){
    glfwInit(); //initialize GLFW

    // tell GLFW what version of OpenGL we are using
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); //configured

    // using CORE profile
    // only modern functions are available
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // create a GLFW window object of 800 by 600 pixels
    GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "AdiPadi Engine", NULL, NULL);

    // error check if the window fails to create
    if(window == NULL){
        std::cout << "Failed to create GLFW Window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window); //introduce the window into current context

    //load glad
    gladLoadGL();

    glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT); //set the viewport size of OpenGL in the window

    Shader shaderProgram(SHADER_DIR "default.vert", SHADER_DIR "default.frag");

    VAO VAO1;
    VAO1.Bind();

    VBO VBO1(vertices, sizeof(vertices));
    EBO EBO1(indices, sizeof(indices));

    // links the VBO to the VAO
    VAO1.LinkVBO(VBO1, 0);
    VAO1.Unbind();
    VBO1.Unbind();
    EBO1.Unbind();

    // main while loop
    while (!glfwWindowShouldClose(window)) //keep the window open until it is closed manually
    {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f); 

        glClear(GL_COLOR_BUFFER_BIT);

        shaderProgram.Activate(); //use the shader program object

        VAO1.Bind(); //bind the VAO (the triangle)

        glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0); //draw the triangle using the 3 vertices in the VAO

        glfwSwapBuffers(window);  //ensures image is swapped each frame

        //checks for any events like keyboard input or mouse movement
        glfwPollEvents(); 
    }
    
    
    // de-allocate all resources once they've outlived their purpose:
    VAO1.Delete();
    VBO1.Delete();
    EBO1.Delete();
    shaderProgram.Delete();

    // delete window before ending the program
    glfwDestroyWindow(window);

    //terminate GLFW before ending the program
    glfwTerminate(); 
    return 0;
}