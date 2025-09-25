#include"shaderClass.h"

std::string get_file_contents(const char* filename)
{
    std::ifstream in(filename, std::ios::binary);
    if(in)
    {
        std::string contents;
        in.seekg(0, std::ios::end);
        contents.resize(in.tellg());
        in.seekg(0, std::ios::beg);
        in.read(&contents[0], contents.size());
        in.close();
        return(contents);
    }
    throw(errno);
}

Shader::Shader(const char* vertexFile, const char* fragmentFile)
{
    std::string vertexCode = get_file_contents(vertexFile);
    std::string fragmentCode = get_file_contents(fragmentFile);

    const char* vertexSource = vertexCode.c_str();
    const char* fragmentSource = fragmentCode.c_str();

    // vertex shader
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER); //create a vertex shader object
    glShaderSource(vertexShader, 1, &vertexSource, NULL); //attach the vertex shader source code to the vertex shader object
    glCompileShader(vertexShader); //compile the vertex shader
    checkCompileErrors(vertexShader, "VERTEX");

    // fragment shader
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER); //create a fragment shader object
    glShaderSource(fragmentShader, 1, &fragmentSource, NULL); //attach the fragment shader source code to the fragment shader object
    glCompileShader(fragmentShader); //compile the fragment shader
    checkCompileErrors(fragmentShader, "FRAGMENT");

    // shader program
    ID = glCreateProgram(); //create a shader program object

    glAttachShader(ID, vertexShader); //attach the vertex shader to the shader program
    glAttachShader(ID, fragmentShader); //attach the fragment shader to the shader program

    glLinkProgram(ID); //link the shader program
    checkCompileErrors(ID, "PROGRAM");

    // Delete shaders since they are linked into our program now and no longer necessary
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

void Shader::Activate()
{
    glUseProgram(ID);
}

void Shader::Delete()
{
    glDeleteProgram(ID);
}

void Shader::checkCompileErrors(unsigned int shader, const char* type){
    GLint hasCompiled;
    char infoLog[1024];
    if(type != "PROGRAM"){
        glGetShaderiv(shader, GL_COMPILE_STATUS, &hasCompiled);
        if(hasCompiled == GL_FALSE){
            glGetShaderInfoLog(shader, 1024, NULL, infoLog);
            std::cout << "SHADER_COMPILATION_ERROR for:" << type << "\n" << infoLog << std::endl;
        }
    }
    else{
        glGetProgramiv(shader, GL_LINK_STATUS, &hasCompiled);
        if(hasCompiled == GL_FALSE){
            glGetProgramInfoLog(shader, 1024, NULL, infoLog);
            std::cout << "SHADER_LINKING_ERROR for:" << type << "\n" << infoLog << std::endl;
        }
    }
}