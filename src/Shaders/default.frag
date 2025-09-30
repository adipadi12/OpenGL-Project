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
uniform vec3 camPos;

void main()
{
   float ambient = 0.20f;

   vec3 normal = normalize(Normal);
   vec3 lightDirection = normalize(lightPos - currentPos);
   float diffuse = max(dot(normal, lightDirection), 0.0f);

   float specularLight = 0.50f;
   vec3 viewDirection = normalize(camPos - currentPos);
   vec3 reflectDirection = reflect(-lightDirection, normal);
   float specAmt = pow(max(dot(viewDirection, reflectDirection), 0.0), 8);
   float specular = specAmt * specularLight;

   FragColor = texture(tex0, texCoord) * lightColor * (diffuse + ambient + specular);
}