#ifndef EBO_CLASS_H
#define EBO_CLASS_H

#include "glad.h"
#include <vector>

class EBO{
    public:
        GLuint ID;
        EBO(std::vector<GLuint>& indices); //GLsizeiptr is a signed integer type used for sizes in OPenGL
        void Bind();
        void Unbind();
        void Delete();
};

#endif