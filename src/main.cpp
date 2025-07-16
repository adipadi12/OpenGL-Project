#include "glad.h"
#include <GLFW/glfw3.h>
#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

int main(){
    glfwInit(); //initialize GLFW
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); //configured
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "Adi's OG Window", NULL, NULL);
    if(window == NULL){
        std::cout << "Failed to create GLFW Window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window); //make the window's context current
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback); //set the framebuffer size callback

    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        std::cout << "GLAD not intitialzed" << std::endl;
        return -1;
    }

    glViewport(0, 0, 800, 600); //set the viewport size


    while (!glfwWindowShouldClose(window))
    {
        /* code */
        glfwSwapBuffers(window); //swap buffers
        glfwPollEvents(); //poll for events
    }
    
    glfwTerminate(); //terminate GLFW
    return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height); //update viewport on window resize
}