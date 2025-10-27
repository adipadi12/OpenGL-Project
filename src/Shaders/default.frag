// fragment shader source code
#version 330 core
out vec4 FragColor;

in vec3 color; // inputs and outputs need to have same name

in vec2 texCoord;
in vec3 Normal;
in vec3 currentPos;

uniform sampler2D tex0;
uniform sampler2D tex1;

uniform vec4 lightColor;
uniform vec3 lightPos;
uniform vec3 camPos;

vec4 pointLight(){
   vec3 lightVec = lightPos - currentPos;
   float dist = length(lightVec);
   float a = 0.05;
   float b = 0.01;
   float inten = 1.0f / (a * dist * dist + b * dist + 1.0f);

   // ambient lighting
   float ambient = 0.20f;

   vec3 normal = normalize(Normal);
   vec3 lightDirection = normalize(lightVec);
   float diffuse = max(dot(normal, lightDirection), 0.0f);

   float specularLight = 0.50f;
   vec3 viewDirection = normalize(camPos - currentPos);
   vec3 reflectDirection = reflect(-lightDirection, normal);
   float specAmt = pow(max(dot(viewDirection, reflectDirection), 0.0), 16);
   float specular = specAmt * specularLight;

   return (texture(tex0, texCoord) *  (diffuse * inten + ambient) + texture(tex1, texCoord).r * specular * inten) * lightColor;
}

vec4 directionLight(){
      // ambient lighting
   float ambient = 0.20f;

   vec3 normal = normalize(Normal);
   vec3 lightDirection = normalize(vec3(1.0f,1.0f,0.0f));
   float diffuse = max(dot(normal, lightDirection), 0.0f);

   float specularLight = 0.50f;
   vec3 viewDirection = normalize(camPos - currentPos);
   vec3 reflectDirection = reflect(-lightDirection, normal);
   float specAmt = pow(max(dot(viewDirection, reflectDirection), 0.0), 16);
   float specular = specAmt * specularLight;

   return (texture(tex0, texCoord) *  (diffuse + ambient) + texture(tex1, texCoord).r * specular) * lightColor;
}

uniform vec3 spotDir;

vec4 spotLight(){
   float outerCone = 0.9f;
   float innerCone = 0.95f; // cosine angles between the 2 make the shader better

   // ambient lighting
   float ambient = 0.20f;

   vec3 normal = normalize(Normal);
   vec3 lightDirection = normalize(lightPos - currentPos);
   float diffuse = max(dot(normal, lightDirection), 0.0f);

   float specularLight = 0.50f;
   vec3 viewDirection = normalize(camPos - currentPos);
   vec3 reflectDirection = reflect(-lightDirection, normal);
   float specAmt = pow(max(dot(viewDirection, reflectDirection), 0.0), 16);
   float specular = specAmt * specularLight;

   float angle = dot(normalize(spotDir), -lightDirection);
   float inten = clamp((angle - outerCone) / (innerCone - outerCone), 0.0f, 1.0f); //formula for intensity

   return (texture(tex0, texCoord) *  (diffuse * inten + ambient) + texture(tex1, texCoord).r * specular * inten) * lightColor;
}

void main()
{
   FragColor = spotLight();
}