#pragma once
#include <map>
#include "types.hpp"
#include "Render/Vertex.h"
#include "utils/String.h"

using namespace Engine;

class Mesh
{
    
public:
    Mesh(float verticesData[], size_t verticesSize, float uv[], size_t uvSize, float normals[], size_t normalsSize, uint32 indices[], size_t indicesSize, const String NewMeshName);
    ~Mesh();
    
    String GetMeshName() const { return MeshName; }
    
    static Mesh* GetMeshByName(const String MeshName);
    
    uint32 GetID() const { return MeshID; }
    
    uint32 GetTotalDrawingVertices() const { return totalDrawingVertices; }
    
    void Draw();
    
    void ConfigureVAO(uint32 VAO);
    
    uint32 GetVAO() { return VAO; }
    
private:
    void ParseVertices(float verticesData[], size_t verticesSize, float uv[], size_t uvSize, float normal[], size_t normalSize);
    
    void ImportMesh(uint32 indices[], size_t indicesSize);
    void CheckGLError(const char* location);

private:
    static uint32 NbMeshes;
    
    uint32 MeshID;
    
    uint32 VAO = 0;
    
    uint32 VBO = 0;
    
    uint32 EBO = 0;
    
    String MeshName;
    
    uint32 AllMeshesIndex;
    
    uint32 verticesCount;
    
    uint32 totalDrawingVertices;
    
    uint32 trianglesCount;
    
    bool hasUV = false;
    
    bool hasNormals = false;
    
    static std::map<const String, Mesh*> AllMeshesMap;
    
    std::vector<Vertex> Vertices;
};
