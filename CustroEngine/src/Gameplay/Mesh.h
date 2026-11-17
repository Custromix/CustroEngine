#pragma once
#include <map>
#include "types.hpp"
#include "Render/Vertex.h"
#include "utils/String.h"

using namespace Engine;

struct MeshData
{
    std::vector<Vertex> Vertices;
    std::vector<uint32> Indices;
};

class Mesh
{
    
public:
    Mesh(const MeshData& NewMeshData, const String NewMeshName);
    ~Mesh();
    
    String GetMeshName() const { return MeshName; }
    
    static Mesh* GetMeshByName(const String MeshName);
    
    uint32 GetID() const { return MeshID; }
    
    uint32 GetTotalDrawingVertices() const { return MyMeshData.Indices.size(); }
    
    void Draw();
    
    void ConfigureVAO(uint32 VAO);
    
    uint32 GetVAO() { return VAO; }
    
private:
    
    void ImportMesh();
    void CheckGLError(const char* location);

private:
    static uint32 NbMeshes;
    
    uint32 MeshID;
    
    uint32 VAO = 0;
    
    uint32 VBO = 0;
    
    uint32 EBO = 0;
    
    String MeshName;
    
    MeshData MyMeshData;
    
    uint32 AllMeshesIndex;
    
    uint32 trianglesCount;
    
    static std::map<const String, Mesh*> AllMeshesMap;
};
