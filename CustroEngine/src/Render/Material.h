#pragma once
#include "Shader.h"
#include "Texture.h"

class MeshComponent;


struct MeshGroup
{
    explicit MeshGroup(MeshComponent* FirstMeshComponent);
    ~MeshGroup();

    MeshGroup(const MeshGroup& other) = delete;
    MeshGroup& operator=(const MeshGroup& other) = delete;

    MeshGroup(MeshGroup&& other) noexcept;
    MeshGroup& operator=(MeshGroup&& other) noexcept;

    void AddMeshComponent(MeshComponent* component);
    void RemoveMeshComponent(MeshComponent* component);
    
    void SetNewMeshComponentToRefresh(MeshComponent* component);
    
    void SetAllInstanceBuffer();
    void RefreshInstanceMinMaxZoneInOnceBuffer(uint32 Min, uint32 Max);
    void RefreshSmallAmountOfInstance(std::vector<uint32> indexList);

    uint32 VAO = 0;
    uint32 VBO = 0;
    uint32 id = 0;
    uint32 NbVertices = 0;
    String name = "";
    std::vector<MeshComponent*> MeshComponents;
    std::vector<glm::mat4> Models;
    bool needRefresh = false;
    uint32 MinIndexToRefresh = -1;
    uint32 MaxIndexToRefresh = 0;
    bool IsBufferSizeChanged = false;
    
};

class Material
{
    
public:
    Material(Shader* existingShader, const String& materialName);
    ~Material();
    
    Shader&  GetShader() const { return *usableShader; }
    
    const std::vector<Texture*>& GetTextures() const { return textures; }
    
    void setBoolean(const std::string& name, bool value);
    void setInteger(const std::string& name, int value);
    void setFloat(const std::string& name, float value);  
    void setVector2(const std::string& name, float x, float y);
    void setVector3(const std::string& name, float x, float y, float z);
    void setVector3(const std::string& name, glm::vec3 vec3);
    void setMatrix4(const std::string& name, glm::mat4 model);
	
    void SetTexture(Texture* texture, String TextureName);
    
    void Subscribe(MeshComponent* component);
    void UnSubscribe(MeshComponent* component);
    void RefreshGroup(MeshComponent* component);
    void OnComponentChanged(MeshComponent* component);
    
    std::vector<MeshGroup>& GetMeshes() { return Meshes; }
	
    static Material* GetMaterialByName(const String name);
protected:
    MeshGroup* FindMeshGroupByMesh(MeshComponent* component);

private:
    
    Shader* usableShader;
    
    String Name;
    
    std::vector<Texture*> textures;
    
    static std::map<const String, Material*> AllMaterialMap;
    
	std::vector<MeshGroup> Meshes;
};
