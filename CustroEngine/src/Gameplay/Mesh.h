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
    
    void Draw();
    
private:
    void ParseVertices(float verticesData[], size_t verticesSize, float uv[], size_t uvSize, float normal[], size_t normalSize);
    
    void ImportMesh(uint32 indices[], size_t indicesSize);
    void CheckGLError(const char* location);

private:
    
    unsigned int VAO = 0;
    
    unsigned int VBO = 0;
    
    unsigned int EBO = 0;
    
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
