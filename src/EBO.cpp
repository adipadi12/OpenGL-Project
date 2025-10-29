#include "EBO.h"

EBO::EBO(std::vector<GLuint>& indices){
    glGenBuffers(1, &ID); //generate 1 buffer for 1 3D object
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID); //bind the buffer to the GL_ARRAY_BUFFER target, makes certain object the current object aka binding object
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), GL_STATIC_DRAW); // STATIC DRAW means the data is set only once and used many times
}

void EBO::Bind(){
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
}

void EBO::Unbind(){
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void EBO::Delete(){
    glDeleteBuffers(1, &ID);
}