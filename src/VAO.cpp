#include "VAO.h"

VAO::VAO(){
    glGenVertexArrays(1, &ID); //generate 1 vertex array object
}

void VAO::LinkAttrib(VBO& VBO, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset){
    VBO.Bind();
    glVertexAttribPointer(layout, numComponents, type, GL_FALSE, stride, offset); //how OpenGL should interpret the vertex data (per vertex attribute)
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