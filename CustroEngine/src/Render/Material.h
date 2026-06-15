#pragma once
#include "Shader.h"
#include "Texture.h"

class Material
{
    
public:
    Material(Shader* existingShader, const String& materialName);
    ~Material();
    
    Shader& GetShader() const { return *usableShader; }
    
    std::vector<Texture*> GetTextures() const { return textures; }
    
    void setBoolean(const std::string& name, bool value);
    void setInteger(const std::string& name, int value);
    void setFloat(const std::string& name, float value);  
    void setVector2(const std::string& name, float x, float y);
    void setVector3(const std::string& name, float x, float y, float z);
    void setVector3(const std::string& name, glm::vec3 vec3);
    void setMatrix4(const std::string& name, glm::mat4 model);
	
    void SetTexture(Texture* texture, String TextureName);
    
    static Material* GetMaterialByName(const String name);

private:
    
    Shader* usableShader;
    
    String Name;
    
    std::vector<Texture*> textures;
    
    static std::map<const String, Material*> AllMaterialMap;
};
