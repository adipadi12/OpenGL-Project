#include "VBO.h"

VBO::VBO(GLfloat* vertices, GLsizeiptr size){
    glGenBuffers(1, &ID); //generate 1 buffer for 1 3D object
    glBindBuffer(GL_ARRAY_BUFFER, ID); //bind the buffer to the GL_ARRAY_BUFFER target, makes certain object the current object aka binding object
    glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW); // STATIC DRAW means the data is set only once and used many times
}

void VBO::Bind(){
    glBindBuffer(GL_ARRAY_BUFFER, ID);
}

void VBO::Unbind(){
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VBO::Delete(){
    glDeleteBuffers(1, &ID);
}