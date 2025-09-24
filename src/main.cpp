#include "glad.h"
#include <GLFW/glfw3.h>
#include <iostream>
#include <cmath>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processsInput(GLFWwindow *window);

const int SCREEN_WIDTH = 1000;
const int SCREEN_HEIGHT = 800;
// vertex shader source code
const char *vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";

// fragment shader source code
const char *fragmentShaderSource = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    "}\n\0";


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

    gladLoadGL(); //load glad

    glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT); //set the viewport size of OpenGL in the window

    // vertex shader compiled from the source code in the GPU during runtime
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER); //create a vertex shader object
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL); //attach the vertex shader source code to the vertex shader object
    glCompileShader(vertexShader); //compile the vertex shader
    
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER); //create a fragment shader object
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL); //attach the fragment shader source code to the fragment shader object
    glCompileShader(fragmentShader); //compile the fragment shader

    // shader program
    GLuint shaderProgram = glCreateProgram(); //create a shader program object
     
    glAttachShader(shaderProgram, vertexShader); //attach the vertex shader to the shader program
    glAttachShader(shaderProgram, fragmentShader); //attach the fragment shader to the shader program

    glLinkProgram(shaderProgram); //link the shader program

    // Delete shaders since they are linked into our program now and no longer necessary
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);


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


    // big batches of vertices sent from CPU to GPU
    GLuint VAO, VBO, EBO; //vertex buffer object, vertex array object

    //always generate VAO before VBO
    glGenVertexArrays(1, &VAO); //generate 1 vertex array object
    glGenBuffers(1, &VBO); //generate 1 buffer for 1 3D object
    glGenBuffers(1, &EBO); //generate 1 element buffer object

    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO); 

    // GL_ARRAY_BUFFER is the type of buffer used for VBO
    glBindBuffer(GL_ARRAY_BUFFER, VBO); //bind the buffer to the GL_ARRAY_BUFFER target, makes certain object the current object aka binding object

    // copy the vertices data into the buffer's memory
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); // STATIC DRAW means the data is set only once and used many times
    // specified to improve performance`

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO); //bind the element buffer object
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW); //copy the indices data into the buffer's memory

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0); //enable the vertex attribute at location 0

    glBindBuffer(GL_ARRAY_BUFFER, 0); //unbind the VBO
    glBindVertexArray(0); //unbind the VAO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); //unbind the EBO after VAO because the EBO is stored in the VAO

    //set clear color
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f); 

    //clear the color buffer and assign the new color to it
    glClear(GL_COLOR_BUFFER_BIT);
    
    //swap back buffer with front buffer
    glfwSwapBuffers(window); 

    while (!glfwWindowShouldClose(window)) //keep the window open until it is closed manually
    {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f); 
        glClear(GL_COLOR_BUFFER_BIT);
        glUseProgram(shaderProgram); //use the shader program object
        glBindVertexArray(VAO); //bind the VAO (the triangle)
        glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0); //draw the triangle using the 3 vertices in the VAO
        glfwSwapBuffers(window);  //ensures image is swapped each frame

        //checks for any events like keyboard input or mouse movement
        glfwPollEvents(); 
    }
    
    // de-allocate all resources once they've outlived their purpose:
    glDeleteVertexArrays(1, &VAO); //delete the vertex array object
    glDeleteBuffers(1, &VBO); //delete the vertex buffer object
    glDeleteBuffers(1, &EBO); //delete the element buffer object
    glDeleteProgram(shaderProgram); //delete the shader program

    // delete window before ending the program
    glfwDestroyWindow(window);

    //terminate GLFW before ending the program
    glfwTerminate(); 
    return 0;
}