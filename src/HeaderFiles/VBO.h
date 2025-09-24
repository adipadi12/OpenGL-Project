#ifndef VBO_CLASS_H
#define VBO_CLASS_H

#include "glad.h"

class VBO{
    public:
        GLuint ID;
        VBO(GLfloat* vertices, GLsizeiptr size); //GLsizeiptr is a signed integer type used for sizes in OPenGL
        void Bind();
        void Unbind();
        void Delete();
};

#endif