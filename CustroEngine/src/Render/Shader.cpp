#include "Shader.h"
#include <fstream>
#include <sstream>
#include <algorithm>

#include "Renderer.h"

std::map<const String, Shader*> Shader::AllShadersMap;

Shader::Shader()
{
    AllShadersMap[Name] = this;
}

Shader::Shader(const String shaderPath, const String shaderName, uint32 programID)
{
    if (shaderName != "")
        Name = shaderName;
    else
        std::cout << "ERROR::SHADER::NAME NOT SET" << std::endl;
    
    
    std::ifstream ShaderFile;
    
    std::cout << "Shader " << shaderName << " : " << shaderPath << std::endl;
    
    ShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    
    try
    {
        ShaderFile.open(shaderPath.CStr());
        std::stringstream ShaderStream;
        ShaderStream << ShaderFile.rdbuf();
        ShaderFile.close();
        
        ShaderCode = ShaderStream.str().c_str();
        
        ProgramID = programID;
        
        AllShadersMap[Name] = this;
    }catch (std::ifstream::failure& e)
    {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ " << e.code() << std::endl;
    }
}

Shader::~Shader()
{
    Renderer::Get().UnSubscribe(this);
}

void Shader::setBoolean(const std::string& name, bool value)
{
    glUniform1i(glGetUniformLocation(ProgramID, name.c_str()), (int)value);
}

void Shader::setInteger(const std::string& name, int value)
{
    glUniform1i(glGetUniformLocation(ProgramID, name.c_str()), value);
}

void Shader::setFloat(const std::string& name, float value)
{
    glUniform1f(glGetUniformLocation(ProgramID, name.c_str()), value);
}

void Shader::setVector2(const std::string& name, float x, float y)
{
    glUniform2f(glGetUniformLocation(ProgramID, name.c_str()), x, y);
}

void Shader::setVector3(const std::string& name, float x, float y, float z)
{
    glUniform3f(glGetUniformLocation(ProgramID, name.c_str()), x, y, z);
}

void Shader::setVector3(const std::string& name, glm::vec3 vec3)
{
    glUniform3f(glGetUniformLocation(ProgramID, name.c_str()), vec3.x, vec3.y, vec3.z);
}
void Shader::setMatrix4(const std::string& name, glm::mat4 model)
{
    glUniformMatrix4fv(glGetUniformLocation(ProgramID, name.c_str()), 1, GL_FALSE, glm::value_ptr(model));
}

void Shader::setMatrix4(int32 location, glm::mat4 model)
{
    glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(model));
}

void Shader::setTexture(const String& name, uint32 slot)
{
    glUniform1i(glGetUniformLocation(ProgramID, name.CStr()), slot);
}

void Shader::Subscribe(Material* mat)
{
    if (std::find(MyMaterials.begin(), MyMaterials.end(), mat) != MyMaterials.end())
        return;
    
    MyMaterials.push_back(mat);
}

void Shader::UnSubscribe(Material* mat)
{
    MyMaterials.erase(std::remove(MyMaterials.begin(), MyMaterials.end(), mat), MyMaterials.end());
}

Shader* Shader::GetShaderByName(const String name)
{
    auto it = AllShadersMap.find(name);
    if (it != AllShadersMap.end())
        return it->second;
    return nullptr;
}
