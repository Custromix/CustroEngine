#include "Shader.h"

Shader::Shader(String vertexPath, String fragmentPath)
{
    std::string vertexCode, fragmentCode;
    std::ifstream vShaderFile, fShaderFile;
    
    std::cout << "Vertex Shader : " << vertexPath << std::endl;
    std::cout << "Fragment Shader : " << fragmentPath << std::endl;
    
    vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    
    try
    {
        vShaderFile.open(vertexPath.CStr());
        fShaderFile.open(fragmentPath.CStr());
        std::stringstream vShaderStream, fShaderStream;
        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();
        
        vShaderFile.close();
        fShaderFile.close();
        
        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();
        
    }catch (std::ifstream::failure& e)
    {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ " << e.code() << std::endl;
    }
    
    const char* vShaderCode = vertexCode.c_str();
    const char* fShaderCode = fragmentCode.c_str();
    
    unsigned int vertexShaderID, fragmentShaderID;
    int  success;
    char infoLog[512];
    
    vertexShaderID = glCreateShader(GL_VERTEX_SHADER); //Créer un shader vide de type GL_VERTEX_SHADER
    
    glShaderSource(vertexShaderID, 1, &vShaderCode, nullptr); //Assign le shader GLSL au vertexShader
    glCompileShader(vertexShaderID); //Compile le vertex shader
    
    glGetShaderiv(vertexShaderID, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(vertexShaderID, 512, nullptr, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    
    fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER); //créer un shader vide de type GL_FRAGMENT_SHADER
    glShaderSource(fragmentShaderID, 1, &fShaderCode, nullptr); //assign le shader GLSL au fragmentShader
    glCompileShader(fragmentShaderID); //compile le fragmentShader
    
    glGetShaderiv(fragmentShaderID, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(fragmentShaderID, 512, nullptr, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    
    ID = glCreateProgram();
    glAttachShader(ID, vertexShaderID);
    glAttachShader(ID, fragmentShaderID);
    glLinkProgram(ID);
    
    
    glGetProgramiv(ID, GL_LINK_STATUS, &success);
    if(!success) {
        glGetProgramInfoLog(ID, 512, nullptr, infoLog);
        std::cout << "ERROR::SHADER_PROGRAM::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    
    glDeleteShader(vertexShaderID);
    glDeleteShader(fragmentShaderID);
}

void Shader::use()
{
    glUseProgram(ID);
}

void Shader::setBoolean(const std::string& name, bool value) const
{
    glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}

void Shader::setInteger(const std::string& name, int value) const
{
    glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setFloat(const std::string& name, float value) const
{
    glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setVector2(const std::string& name, float x, float y) const
{
    glUniform2f(glGetUniformLocation(ID, name.c_str()), x, y);
}

void Shader::setVector3(const std::string& name, float x, float y, float z) const
{
    glUniform3f(glGetUniformLocation(ID, name.c_str()), x, y, z);
}

void Shader::setVector3(const std::string& name, glm::vec3 vec3) const
{
    glUniform3f(glGetUniformLocation(ID, name.c_str()), vec3.x, vec3.y, vec3.z);
}
void Shader::setMatrix4(const std::string& name, glm::mat4 model) const
{
    glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, glm::value_ptr(model));
}
