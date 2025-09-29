// vertex shader source code
#version 330 core //version of glsl
layout (location = 0) in vec3 aPos; // input a class
layout (location = 1) in vec3 aColor; 
layout (location = 2) in vec2 aTex;

out vec3 color;

out vec2 texCoord;

uniform float scale; // only declare uniforms when gonna use them else error goes BOOM

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj; 

void main()
{
   gl_Position = proj * view * model * vec4(aPos, 1.0); // w component is 1 for position vectors
   color = aColor;
   texCoord = aTex;
}