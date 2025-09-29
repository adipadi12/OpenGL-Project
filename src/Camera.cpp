#include "Camera.h"

Camera::Camera(int width, int height, glm::vec3 position)
{
    Camera::width = width;
    Camera::height = height;
    Position = position;
    //glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED); //hide the cursor
}

void Camera::Matrix(float FOVdeg, float nearPlane, float farPlane, Shader& shader, const char* uniform)
{
    glm::mat4 view = glm::mat4(1.0f);
    glm::mat4 proj = glm::mat4(1.0f);

    view = glm::lookAt(Position, Position + Orientation, Up); //view matrix
    proj = glm::perspective(glm::radians(FOVdeg), (float)width / (float)height, nearPlane, farPlane); //projection matrix

    glUniformMatrix4fv(glGetUniformLocation(shader.ID, uniform), 1, GL_FALSE, glm::value_ptr(proj * view)); //send to vertex shader
}