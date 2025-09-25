#ifndef VAO_CLASS_H
#define VAO_CLASS_H

#include "glad.h"
#include "VBO.h"

class VAO{
    public:
        GLuint ID;
        VAO();
        //STRIDE IS distance in bytes between beginning of consecutive vertex attributes 
        // OFFSET is offset of the first component of the first vertex attribute in the array in bytes
        void LinkAttrib(VBO& VBO, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset);
        void Bind();
        void Unbind();
        void Delete();
};

#endif