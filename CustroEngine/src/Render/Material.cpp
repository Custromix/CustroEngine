#include "Material.h"

std::map<const String, Material*> Material::AllMaterialMap;

Material::Material(Shader* existingShader, const String& materialName)
{
    usableShader = existingShader;
    Name = materialName;
    AllMaterialMap[Name] = this;
}

Material::~Material()
{
    usableShader = nullptr;
    textures.clear();
}

void Material::setBoolean(const std::string& name, bool value)
{
    usableShader->setBoolean(name, value);
}

void Material::setInteger(const std::string& name, int value)
{
    usableShader->setInteger(name, value);
}

void Material::setFloat(const std::string& name, float value)
{
    usableShader->setFloat(name, value);
}

void Material::setVector2(const std::string& name, float x, float y)
{
    usableShader->setVector2(name, x, y);
}

void Material::setVector3(const std::string& name, float x, float y, float z)
{
    usableShader->setVector3(name, x, y, z);
}

void Material::setVector3(const std::string& name, glm::vec3 vec3)
{
    usableShader->setVector3(name, vec3);
}
void Material::setMatrix4(const std::string& name, glm::mat4 model)
{
    usableShader->setMatrix4(name, model);
}

void Material::SetTexture(Texture* texture, String TextureName)
{
    if (!texture)
    {
        std::cout << "ERROR::SHADER::TEXTURE NOT SET ligne 51" << std::endl;
        return;
    }
    
    glUseProgram(usableShader->GetProgramID());

    const uint32 slot = textures.size();
    textures.push_back(texture);
    
    usableShader->setTexture(TextureName, slot);
}

Material* Material::GetMaterialByName(const String name)
{
    auto it = AllMaterialMap.find(name);
    if (it != AllMaterialMap.end())
        return it->second;
    return nullptr;
}
