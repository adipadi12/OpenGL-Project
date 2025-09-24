#ifndef EBO_CLASS_H
#define EBO_CLASS_H

#include "glad.h"

class EBO{
    public:
        GLuint ID;
        EBO(GLuint* indices, GLsizeiptr size); //GLsizeiptr is a signed integer type used for sizes in OPenGL
        void Bind();
        void Unbind();
        void Delete();
};

#endif