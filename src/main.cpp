#include<filesystem>
namespace fs = std::filesystem;
#include "Mesh.h"

// can use normal floats but safer to use GLfloats
Vertex vertices[] =
{ //               COORDINATES           /            COLORS          /           NORMALS         /       TEXTURE COORDINATES    //
	Vertex{glm::vec3(-1.0f, 0.0f,  1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f)},
	Vertex{glm::vec3(-1.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 1.0f)},
	Vertex{glm::vec3( 1.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 1.0f)},
	Vertex{glm::vec3( 1.0f, 0.0f,  1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 0.0f)}
};

// Indices for vertices order
GLuint indices[] =
{
	0, 1, 2,
	0, 2, 3
};

Vertex lightVertices[] =
{ //     COORDINATES     //
	Vertex{glm::vec3(-0.1f, -0.1f,  0.1f)},
	Vertex{glm::vec3(-0.1f, -0.1f, -0.1f)},
	Vertex{glm::vec3(0.1f, -0.1f, -0.1f)},
	Vertex{glm::vec3(0.1f, -0.1f,  0.1f)},
	Vertex{glm::vec3(-0.1f,  0.1f,  0.1f)},
	Vertex{glm::vec3(-0.1f,  0.1f, -0.1f)},
	Vertex{glm::vec3(0.1f,  0.1f, -0.1f)},
	Vertex{glm::vec3(0.1f,  0.1f,  0.1f)}
};

GLuint lightSourceIndices[] = {
    0, 1, 2,
    0, 2, 3,
    0, 4, 7,
    0, 7, 3,
    3, 7, 6,
    3, 6, 2,
    2, 6, 5,
    2, 5, 1,
    1, 5, 4,
    1, 4, 0,
    4, 5, 6,
    4, 6, 7
};

const int SCREEN_WIDTH = 1000;
const int SCREEN_HEIGHT = 800;

int main(){
    glfwInit(); //initialize GLFW

    // tell GLFW what version of OpenGL we are using
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); //configured

    // using CORE profile
    // only modern functions are available
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // create a GLFW window object of 800 by 600 pixels
    GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "AdiPadi Engine", NULL, NULL);

    // error check if the window fails to create
    if(window == NULL){
        std::cout << "Failed to create GLFW Window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window); //introduce the window into current context

    //load glad
    gladLoadGL();

    glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT); //set the viewport size of OpenGL in the window

    std::string parentDir = (fs::current_path().fs::path::parent_path()).string();
	std::string texPath = "/src/Resources/";

    Texture textures[]{
        Texture((parentDir + texPath + "planks.png").c_str(), "diffuse", 0, GL_RGBA, GL_UNSIGNED_BYTE), //RGB with jpeg and RGBA with png and jpg
        Texture((parentDir + texPath + "planksSpec.png").c_str(), "specular", 1, GL_RED, GL_UNSIGNED_BYTE)
    };

    // generates shader object using shaders default.vert and default.frag
    Shader shaderProgram(SHADER_DIR "default.vert", SHADER_DIR "default.frag");

    std::vector <Vertex> verts(vertices, vertices + sizeof(vertices) / sizeof(Vertex));
    std::vector <GLuint> inds(indices, indices + sizeof(indices) / sizeof(GLuint));
    std::vector <Texture> texs{textures, textures + sizeof(textures) / sizeof(Texture)};
    Mesh floor(verts, inds, texs);

    // shader for light cube using light.vert and light.frag
    Shader lightShader(SHADER_DIR "light.vert", SHADER_DIR "light.frag");

    std::vector <Vertex> lightVerts(lightVertices, lightVertices + sizeof(lightVertices) / sizeof(Vertex));
    std::vector <GLuint> lightInds(lightSourceIndices, lightSourceIndices + sizeof(lightSourceIndices) / sizeof(GLuint));
    Mesh light(lightVerts, lightInds, texs);



    glm::vec4 lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
    glm::vec3 lightPos = glm::vec3(0.5f, 0.5f, 0.5f);
    glm::mat4 lightModel = glm::mat4(1.0f);
    lightModel = glm::translate(lightModel, lightPos);

    glm::vec3 pyramidPos = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::mat4 pyramidModel = glm::mat4(1.0f);
    pyramidModel = glm::translate(pyramidModel, pyramidPos);

    lightShader.Activate();
    glUniformMatrix4fv(glGetUniformLocation(lightShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(lightModel));
    glUniform4f(glGetUniformLocation(lightShader.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
    shaderProgram.Activate();
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram.ID, "model"), 1, GL_FALSE, glm::value_ptr(pyramidModel));
    glUniform4f(glGetUniformLocation(shaderProgram.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
    glUniform3f(glGetUniformLocation(shaderProgram.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);


    glEnable(GL_DEPTH_TEST); //enable depth testing for 3D

    Camera camera(SCREEN_WIDTH, SCREEN_HEIGHT, glm::vec3(0.0f, 0.25f, 2.0f));
    // main while loop
    while (!glfwWindowShouldClose(window)) //keep the window open until it is closed manually
    {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f); 

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clear the window (with color) and also clear the depth buffer

        

        camera.Inputs(window);

        camera.updateMatrix(45.0f, 0.1f, 100.0f); //send projection and view matrix to shader each frame

        floor.Draw(shaderProgram, camera);
        light.Draw(lightShader, camera);

        glfwSwapBuffers(window);  //ensures image is swapped each frame

        //checks for any events like keyboard input or mouse movement
        glfwPollEvents(); 
    }
    
    
    // de-allocate all resources once they've outlived their purpose:
    shaderProgram.Delete();
    lightShader.Delete();
    // delete window before ending the program
    glfwDestroyWindow(window);

    //terminate GLFW before ending the program
    glfwTerminate(); 
    return 0;
}