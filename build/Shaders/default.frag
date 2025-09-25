// fragment shader source code
#version 330 core
out vec4 FragColor;

in vec3 color; // inputs and outputs need to have same name

void main()
{
   FragColor = vec4(color, 1.0f);
}