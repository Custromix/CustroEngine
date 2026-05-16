#pragma once
#include <map>
#include "types.hpp"
#include "Components/Transform.h"
#include "utils/String.h"

using namespace Engine;

class Mesh
{
    
public:
    Mesh(float vertices[], size_t verticesSize, uint32 indices[], size_t indicesSize, const String NewMeshName);
    ~Mesh();
    
    String GetMeshName() const { return MeshName; }
    
    static Mesh* GetMeshByName(const String MeshName);
    
    void Render();
    
private:
    void ImportMesh(float vertices[], size_t verticesSize, uint32 indices[], size_t indicesSize);
    
private:
    
    unsigned int VAO = 0;
    
    unsigned int VBO;
    
    unsigned int EBO;
    
    String MeshName;
    
    uint32 AllMeshesIndex;
    
    uint32 verticesCount;
    
    static std::map<const String, Mesh*> AllMeshesMap;
};
