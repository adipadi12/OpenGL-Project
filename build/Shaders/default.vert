// vertex shader source code
#version 330 core //version of glsl

// position/coordinates
layout (location = 0) in vec3 aPos; 
// normals
layout (location = 1) in vec3 aNormal;
// colors
layout (location = 2) in vec3 aColor; 
// texture coordinates
layout (location = 3) in vec2 aTex;

// outputs current pos of fragment shader
out vec3 currentPos;
// outputs normal for the fragment shader
out vec3 Normal;
// color for fs
out vec3 color;
// texture coordinates for fs
out vec2 texCoord;


uniform mat4 camMatrix; // camera matrix (view matrix)
uniform mat4 model;

void main()
{
   // caculates current position
   currentPos = vec3(model * vec4(aPos, 1.0f));

   // assisgns the normal from vertext data to Normal
   Normal = aNormal;

   // assigns color from vertex data
   color = aColor;

   // assigns texture coordinates from vertex data
   texCoord = aTex;

   // outputs position/coordinates of all vertices
   gl_Position = camMatrix * vec4(currentPos, 1.0); // w component is 1 for position vectors

}