#include <iostream>
#include "glad.h"
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <cmath>

#include "shaderClass.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"
#include "stb_image.h"
#include "Texture.h"
#include "Camera.h"

// can use normal floats but safer to use GLfloats
GLfloat vertices[] = {
    // COORDINATES        // COLORS               // COORDINATES  
    -0.5f, 0.0f, 0.5f,    0.83f, 0.70f, 0.44f,    0.0f, 0.0f, 
    -0.5f, 0.0f, -0.5f,   0.83f, 0.70f, 0.44f,    5.0f, 0.0f, 
    0.5f,  0.0f, -0.5f,   0.83f, 0.70f, 0.44f,    0.0f, 0.0f, 
    0.5f, 0.0f, 0.5f,     0.83f, 0.70f, 0.44f,    5.0f, 2.5f, 
    0.0f, 0.8f, 0.0f,     0.92f, 0.86f, 0.76f,    2.5f, 5.0f  
};

GLuint indices[] = {
    0, 1, 2, 
    0, 2, 3, 
    0, 1, 4, 
    1, 2, 4, 
    2, 3, 4, 
    3, 0, 4  
};

const int SCREEN_WIDTH = 1200;
const int SCREEN_HEIGHT = 1000;

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
    VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0); //link VBO1 to layout 0 (position)
    VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float))); //link VBO1 to layout 1 (color)
    VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float))); //link VBO1 to layout 2 (texture coords)
    VAO1.Unbind();
    VBO1.Unbind();
    EBO1.Unbind();

    GLuint uniID = glGetUniformLocation(shaderProgram.ID, "scale");

    // texture
    Texture texture(TEXTURE_DIR "doakes2.jpeg", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGB, GL_UNSIGNED_BYTE); //RGB with jpeg and RGBA with png and jpg
    texture.texUnit(shaderProgram, "tex0", 0);

    glEnable(GL_DEPTH_TEST); //enable depth testing for 3D

    // main while loop
    while (!glfwWindowShouldClose(window)) //keep the window open until it is closed manually
    {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f); 

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clear the window (with color) and also clear the depth buffer

        shaderProgram.Activate(); //use the shader program object

        glm::mat4 model = glm::mat4(1.0f); // initialize matrix to identity matrix
        glm::mat4 view = glm::mat4(1.0f);
        glm::mat4 proj = glm::mat4(1.0f);

        model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(0.0f, 1.0f, 0.0f)); //rotate the model over time
        view = glm::translate(view, glm::vec3(0.0f, -0.25f, -2.0f)); //move the scene backwards (so we can see it)
        proj = glm::perspective(glm::radians(45.0f), (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 0.1f, 100.0f); //perspective projection

        int modelLoc = glGetUniformLocation(shaderProgram.ID, "model");
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

        int viewLoc = glGetUniformLocation(shaderProgram.ID, "view");
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

        int projLoc = glGetUniformLocation(shaderProgram.ID, "proj");
        glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(proj));

        glUniform1f(uniID, (sin(glfwGetTime()) / 2.0f) + 0.5f); // send uniform data to the vertex shader
        texture.Bind();

        VAO1.Bind(); //bind the VAO (the triangle)

        glDrawElements(GL_TRIANGLES, sizeof(indices)/sizeof(int), GL_UNSIGNED_INT, 0); //draw the triangle using the 3 vertices in the VAO

        glfwSwapBuffers(window);  //ensures image is swapped each frame

        //checks for any events like keyboard input or mouse movement
        glfwPollEvents(); 
    }
    
    
    // de-allocate all resources once they've outlived their purpose:
    VAO1.Delete();
    VBO1.Delete();
    EBO1.Delete();
    texture.Delete();
    shaderProgram.Delete();

    // delete window before ending the program
    glfwDestroyWindow(window);

    //terminate GLFW before ending the program
    glfwTerminate(); 
    return 0;
}