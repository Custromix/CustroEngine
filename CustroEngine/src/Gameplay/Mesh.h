#pragma once
#include <map>
#include <vector>

#include "types.hpp"
#include "Components/Transform.h"

using namespace Engine;

class Mesh
{
    
public:
    Mesh(float vertices[], const char NewMeshName[255]);
    ~Mesh();
    
    const char* GetMeshName() const { return MeshName; }
    
    static Mesh* GetMeshByName(const char* MeshName) { return AllMeshesMap[MeshName]; }
    
private:
    void ImportMesh(float vertices[]);
    
private:
    
    unsigned int VAO;
    
    unsigned int VBO;
    
    unsigned int EBO;
    
    const char* MeshName;
    
    uint32 AllMeshesIndex;
    
    
    static std::vector<Mesh*> AllMeshes;
    static std::map<const char*, Mesh*> AllMeshesMap;
};
