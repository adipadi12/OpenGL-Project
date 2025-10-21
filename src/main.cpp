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
GLfloat vertices[] =
{ //     COORDINATES     /        COLORS        /    TexCoord    /       NORMALS     //
	-1.0f, 0.0f,  1.0f,		0.0f, 0.0f, 0.0f,		0.0f, 0.0f,		0.0f, 1.0f, 0.0f,
	-1.0f, 0.0f, -1.0f,		0.0f, 0.0f, 0.0f,		0.0f, 1.0f,		0.0f, 1.0f, 0.0f,
	 1.0f, 0.0f, -1.0f,		0.0f, 0.0f, 0.0f,		1.0f, 1.0f,		0.0f, 1.0f, 0.0f,
	 1.0f, 0.0f,  1.0f,		0.0f, 0.0f, 0.0f,		1.0f, 0.0f,		0.0f, 1.0f, 0.0f
};

// Indices for vertices order
GLuint indices[] =
{
	0, 1, 2,
	0, 2, 3
};

GLfloat lightSourceVertices[] = {
    -0.1f, -0.1f, 0.1f,
    -0.1f, -0.1f, -0.1f,
    0.1f, -0.1f, -0.1f,
    0.1f, -0.1f, 0.1f,
    -0.1f, 0.1f, 0.1f,
    -0.1f, 0.1f, -0.1f,
    0.1f, 0.1f, -0.1f,
    0.1f, 0.1f, 0.1f
};

GLuint lightSourceIndices[] = {
    0, 1, 2,
    0, 2, 3,
    0, 4, 7,
    0, 7, 3,
    3, 7, 6,
    3, 6, 2,
    2, 6, 5,
    2, 5, 1,
    1, 5, 4,
    1, 4, 0,
    4, 5, 6,
    4, 6, 7
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
    VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 11 * sizeof(float), (void*)0); //link VBO1 to layout 0 (position)
    VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 11 * sizeof(float), (void*)(3 * sizeof(float))); //link VBO1 to layout 1 (color)
    VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 11 * sizeof(float), (void*)(6 * sizeof(float))); //link VBO1 to layout 2 (texture coords)
    VAO1.LinkAttrib(VBO1, 3, 3, GL_FLOAT, 11 * sizeof(float), (void*)(8 * sizeof(float)));
    VAO1.Unbind();
    VBO1.Unbind();
    EBO1.Unbind();

    Shader lightShader(SHADER_DIR "light.vert", SHADER_DIR "light.frag");

    VAO lightVAO;
    lightVAO.Bind();

    VBO lightVBO(lightSourceVertices, sizeof(lightSourceVertices));
    EBO lightEBO(lightSourceIndices, sizeof(lightSourceIndices));

    lightVAO.LinkAttrib(lightVBO, 0, 3, GL_FLOAT, 3 * sizeof(float), (void*)0); //link lightVBO to layout 0 (position)

    lightVAO.Unbind();
    lightVBO.Unbind();
    lightEBO.Unbind();

    glm::vec4 lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);

    glm::vec3 lightPos = glm::vec3(0.5f, 0.5f, 0.5f);
    glm::mat4 lightModel = glm::mat4(1.0f);
    lightModel = glm::translate(lightModel, lightPos);

    glm::vec3 pyramidPos = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::mat4 pyramidModel = glm::mat4(1.0f);
    pyramidModel = glm::translate(pyramidModel, pyramidPos);

    lightShader.Activate();
    glUniformMatrix4fv(glGetUniformLocation(lightShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(lightModel));
    glUniform4f(glGetUniformLocation(lightShader.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
    shaderProgram.Activate();
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram.ID, "model"), 1, GL_FALSE, glm::value_ptr(pyramidModel));
    glUniform4f(glGetUniformLocation(shaderProgram.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
    glUniform3f(glGetUniformLocation(shaderProgram.ID, "lightPos"), lightPos.x, lightPos.y, lightColor.z);

    // texture
    Texture texture(TEXTURE_DIR "planks.png", GL_TEXTURE_2D, 0, GL_RGBA, GL_UNSIGNED_BYTE); //RGB with jpeg and RGBA with png and jpg
    texture.texUnit(shaderProgram, "tex0", 0);

    Texture plankSpec(TEXTURE_DIR "planksSpec.png", GL_TEXTURE_2D, 1, GL_RED, GL_UNSIGNED_BYTE);
    plankSpec.texUnit(shaderProgram, "tex1", 1);

    glEnable(GL_DEPTH_TEST); //enable depth testing for 3D

    Camera camera(SCREEN_WIDTH, SCREEN_HEIGHT, glm::vec3(0.0f, 0.25f, 2.0f));
    // main while loop
    while (!glfwWindowShouldClose(window)) //keep the window open until it is closed manually
    {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f); 

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clear the window (with color) and also clear the depth buffer

        

        camera.Inputs(window);

        camera.updateMatrix(45.0f, 0.1f, 100.0f); //send projection and view matrix to shader each frame

        shaderProgram.Activate();
        glUniform3f(glGetUniformLocation(shaderProgram.ID, "camPos"), camera.Position.x, camera.Position.y, camera.Position.z);
        camera.Matrix(shaderProgram, "camMatrix");

        texture.Bind();
        plankSpec.Bind();

        VAO1.Bind(); //bind the VAO (the triangle)

        glDrawElements(GL_TRIANGLES, sizeof(indices)/sizeof(int), GL_UNSIGNED_INT, 0); //draw the triangle using the 3 vertices in the VAO

        lightShader.Activate();
        camera.Matrix(lightShader, "camMatrix");
        lightVAO.Bind();
        glDrawElements(GL_TRIANGLES, sizeof(lightSourceIndices)/sizeof(int), GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);  //ensures image is swapped each frame

        //checks for any events like keyboard input or mouse movement
        glfwPollEvents(); 
    }
    
    
    // de-allocate all resources once they've outlived their purpose:
    VAO1.Delete();
    VBO1.Delete();
    EBO1.Delete();
    texture.Delete();
    plankSpec.Delete();
    shaderProgram.Delete();

    // delete window before ending the program
    glfwDestroyWindow(window);

    //terminate GLFW before ending the program
    glfwTerminate(); 
    return 0;
}