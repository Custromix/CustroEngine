#pragma once
#include <map>
#include "types.hpp"
#include "Components/Transform.h"
#include "utils/String.h"

using namespace Engine;

class Mesh
{
    
public:
    Mesh(float vertices[], const String NewMeshName);
    ~Mesh();
    
    String GetMeshName() const { return MeshName; }
    
    static Mesh* GetMeshByName(const String MeshName);
    
private:
    void ImportMesh(float vertices[]);
    
private:
    
    unsigned int VAO;
    
    unsigned int VBO;
    
    unsigned int EBO;
    
    String MeshName;
    
    uint32 AllMeshesIndex;
    
    
    static std::map<const String, Mesh*> AllMeshesMap;
};
