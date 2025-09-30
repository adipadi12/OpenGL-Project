// fragment shader source code
#version 330 core
out vec4 FragColor;

in vec3 color; // inputs and outputs need to have same name

in vec2 texCoord;
in vec3 Normal;
in vec3 currentPos;

uniform sampler2D tex0;

uniform vec4 lightColor;
uniform vec3 lightPos;

void main()
{
   float ambient = 0.20f;

   vec3 normal = normalize(Normal);
   vec3 lightDirection = normalize(lightPos - currentPos);

   float diffuse = max(dot(normal, lightDirection), 0.0f);
   FragColor = texture(tex0, texCoord) * lightColor * (diffuse + ambient);
}