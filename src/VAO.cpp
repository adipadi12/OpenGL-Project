#include "VAO.h"

VAO::VAO(){
    glGenVertexArrays(1, &ID); //generate 1 vertex array object
}

void VAO::LinkVBO(VBO& VBO, GLuint layout){
    VBO.Bind();
    glVertexAttribPointer(layout, 3, GL_FLOAT, GL_FALSE, 0, (void*)0); //how OpenGL should interpret the vertex data (per vertex attribute)
    glEnableVertexAttribArray(layout);
    VBO.Unbind();
}

void VAO::Bind(){
    glBindVertexArray(ID);
}

void VAO::Unbind(){
    glBindVertexArray(0);
}

void VAO::Delete(){
    glDeleteVertexArrays(1, &ID);
}