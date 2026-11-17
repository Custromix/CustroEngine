#include "Material.h"
#include <algorithm>
#include "Gameplay/Components/EntityComponents/SpatialComponents/MeshComponent.h"

// ================= MeshGroup =================

MeshGroup::MeshGroup(MeshComponent* FirstMeshComponent)
{
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)0);
    glEnableVertexAttribArray(3);
    glVertexAttribDivisor(3, 1);

    glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)sizeof(glm::vec4));
    glEnableVertexAttribArray(4);
    glVertexAttribDivisor(4, 1);

    glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(sizeof(glm::vec4) * 2));
    glEnableVertexAttribArray(5);
    glVertexAttribDivisor(5, 1);

    glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(sizeof(glm::vec4) * 3));
    glEnableVertexAttribArray(6);
    glVertexAttribDivisor(6, 1);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    Mesh* mesh = FirstMeshComponent->GetMesh();
    mesh->ConfigureVAO(VAO);
    id = mesh->GetID();
    name = String("Group_") + mesh->GetMeshName();
    NbVertices = mesh->GetTotalDrawingVertices();

    MeshComponents.push_back(FirstMeshComponent);
    FirstMeshComponent->indexInGroup = MeshComponents.size() - 1;
    IsBufferSizeChanged = true;
}

MeshGroup::~MeshGroup()
{
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}

MeshGroup::MeshGroup(MeshGroup&& other) noexcept
{
    VAO = other.VAO;
    VBO = other.VBO;
    id = other.id;
    NbVertices = other.NbVertices;
    name = std::move(other.name);
    MeshComponents = std::move(other.MeshComponents);
    Models = std::move(other.Models);
    needRefresh = other.needRefresh;
    MinIndexToRefresh = other.MinIndexToRefresh;
    MaxIndexToRefresh = other.MaxIndexToRefresh;
    IsBufferSizeChanged = other.IsBufferSizeChanged;
    
    other.VAO = 0;
    other.VBO = 0;
}

MeshGroup& MeshGroup::operator=(MeshGroup&& other) noexcept
{
    if (this != &other)
    {
        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);

        VAO = other.VAO;
        VBO = other.VBO;
        id = other.id;
        NbVertices = other.NbVertices;
        name = std::move(other.name);
        MeshComponents = std::move(other.MeshComponents);
        Models = std::move(other.Models);
        needRefresh = other.needRefresh;
        MinIndexToRefresh = other.MinIndexToRefresh;
        MaxIndexToRefresh = other.MaxIndexToRefresh;
        IsBufferSizeChanged = other.IsBufferSizeChanged;

        other.VAO = 0;
        other.VBO = 0;
    }
    return *this;
}

void MeshGroup::AddMeshComponent(MeshComponent* component)
{
    MeshComponents.push_back(component);
    component->indexInGroup = MeshComponents.size() - 1;
    IsBufferSizeChanged = true;
}

void MeshGroup::RemoveMeshComponent(MeshComponent* component)
{
    uint32 indexToSwap = component->indexInGroup;
    
    if (indexToSwap >= MeshComponents.size())
        return;

    if (MeshComponents[indexToSwap] != component)
        return;
    
    MeshComponents[indexToSwap] = MeshComponents.back();
    MeshComponents[indexToSwap]->indexInGroup = indexToSwap;
    MeshComponents.pop_back();
    component->indexInGroup = -1;
    
    IsBufferSizeChanged = true;
}

void MeshGroup::SetNewMeshComponentToRefresh(MeshComponent* component)
{
    if (!component)
        return;
    
    uint32 index = component->indexInGroup;
    if (index == -1)
        return;
    
    if (index < MinIndexToRefresh)
        MinIndexToRefresh = index;
    if (index > MaxIndexToRefresh)
        MaxIndexToRefresh = index;
    needRefresh = true;
}

void MeshGroup::SetAllInstanceBuffer()
{
    Models.clear();
    for (MeshComponent* mComp : MeshComponents)
        Models.push_back(mComp->GetTransform().GetWorldModel());
    
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::mat4) * Models.size(), Models.data(), GL_DYNAMIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    
    needRefresh = false;
    IsBufferSizeChanged = false;
    
    MinIndexToRefresh = -1;
    MaxIndexToRefresh = 0;
}

void MeshGroup::RefreshSmallAmountOfInstance(std::vector<uint32> indexList)
{
    Models.clear();
    for (MeshComponent* mComp : MeshComponents)
        Models.push_back(mComp->GetTransform().GetWorldModel());
    
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    for (uint32 index : indexList)
    {
        glBufferSubData(GL_ARRAY_BUFFER, index * sizeof(glm::mat4), sizeof(glm::mat4), &Models[index]);
    }
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    
    needRefresh = false;
}

void MeshGroup::RefreshInstanceMinMaxZoneInOnceBuffer(uint32 Min, uint32 Max)
{
    for (int i = Min; i <= Max; ++i)
    {
        Models[i] = MeshComponents[i]->GetTransform().GetWorldModel();
    }
    
    uint32 size = Max - Min + 1;
    
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferSubData(GL_ARRAY_BUFFER, sizeof(glm::mat4) * Min, sizeof(glm::mat4) * size, &Models[Min]);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    
    needRefresh = false;
    MinIndexToRefresh = -1;
    MaxIndexToRefresh = 0;
}

// ================= Material =================


std::map<const String, Material*> Material::AllMaterialMap;

Material::Material(Shader* existingShader, const String& materialName)
{
    usableShader = existingShader;
    Name = materialName;
    AllMaterialMap[Name] = this;
    usableShader->Subscribe(this);
}

Material::~Material()
{
    AllMaterialMap.erase(Name);
    usableShader->UnSubscribe(this);
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

void Material::Subscribe(MeshComponent* component)
{
    if(!component->GetMesh() || !component->IsActive())
        return;
    
    auto* FindingMeshGroup = FindMeshGroupByMesh(component);
    
    if (FindingMeshGroup)
        FindingMeshGroup->AddMeshComponent(component);
    else
        Meshes.emplace_back(component);   
    
}

void Material::UnSubscribe(MeshComponent* component)
{
    for (MeshGroup& mGroup : Meshes)
        mGroup.RemoveMeshComponent(component);
}

void Material::RefreshGroup(MeshComponent* component)
{
    UnSubscribe(component);
    Subscribe(component);
}

void Material::OnComponentChanged(MeshComponent* component)
{
    if (!component->GetMesh() || !component->IsActive())
        return;
    
    auto* FindingMeshGroup = FindMeshGroupByMesh(component);
    
    if (!FindingMeshGroup)
        return;
    
    FindingMeshGroup->SetNewMeshComponentToRefresh(component);
}


Material* Material::GetMaterialByName(const String name)
{
    auto it = AllMaterialMap.find(name);
    if (it != AllMaterialMap.end())
        return it->second;
    return nullptr;
}

MeshGroup* Material::FindMeshGroupByMesh(MeshComponent* component)
{
    for (int i = 0; i < Meshes.size(); ++i)
    {
        if (component->GetMesh()->GetID() == Meshes[i].id)
        {
            return &Meshes[i];
        }
    }

    return nullptr;
}
