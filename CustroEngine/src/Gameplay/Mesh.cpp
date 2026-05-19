#include "Mesh.h"

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Render/Vertex.h"

std::map<const String, Mesh*> Mesh::AllMeshesMap;

Mesh::Mesh(float verticesData[], size_t verticesSize, float uv[], size_t uvSize, float normals[], size_t normalsSize, uint32 indices[], size_t indicesSize, const String NewMeshName)
{
    

    MeshName = NewMeshName;
    verticesCount = verticesSize/(sizeof(float)*3);
    totalDrawingVertices = indicesSize/sizeof(uint32);
    trianglesCount = indicesSize/(sizeof(uint32)*3);
    
    std::cout << "verticesCount: " << verticesCount << std::endl;
    std::cout << "facesCount: " << trianglesCount << std::endl;
    
    AllMeshesMap[MeshName] = this;
    
    ParseVertices(verticesData, verticesSize, uv, uvSize, normals, normalsSize);
    ImportMesh(indices, indicesSize);
}

Mesh::~Mesh()
{
    std::cout << "Mesh destroyed: " << MeshName << " VAO: " << VAO << std::endl;
    AllMeshesMap.erase(MeshName);
}

Mesh* Mesh::GetMeshByName(const String MeshName)
{
    auto it = AllMeshesMap.find(MeshName);
    if (it != AllMeshesMap.end())
        return it->second;
    return nullptr;
}

void Mesh::Draw()
{
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, totalDrawingVertices, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void Mesh::ParseVertices(float verticesData[], size_t verticesSize, float uv[], size_t uvSize, float normal[], size_t normalSize)
{
    if (verticesCount == 0)
    {
        std::cout << "\033[31m" << "ERROR::VerticesCount == 0" << "\033[0m" << std::endl;
        return;
    }
    
    for (uint32 i = 0; i < verticesCount; ++i)
    {
        Vertex v;
        
        if (verticesSize > 0)
            v.position      = glm::vec3(verticesData[i * 3], verticesData[i * 3 + 1], verticesData[i * 3 + 2]);
        
        if (uvSize > 0)
        {
            v.uv            = glm::vec2(uv[i * 2], uv[i * 2 + 1]);
            hasUV = true;
        }
        
        if (normalSize > 0)
        {
            v.normal        = glm::vec3(normal[i * 3], normal[i * 3 + 1], normal[i * 3 + 2]);
            hasNormals = true;
        }
        
        Vertices.push_back(v);
    }
}

void Mesh::ImportMesh(uint32 indices[], size_t indicesSize)
{
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &EBO);
    glGenBuffers(1, &VBO);
    
    if (VAO == 0 || EBO == 0 || VBO == 0)
    {
        std::cerr << "Erreur : VAO, VBO ou EBO non générés" << std::endl;
    }
    
    std::cout << "verticesCount = " << verticesCount << std::endl;
    std::cout << "Vertices.size() = " << Vertices.size() << std::endl;
    
    glBindVertexArray(VAO);
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesSize, indices, GL_STATIC_DRAW);
    
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER,  sizeof(Vertex) * Vertices.size(),  Vertices.data(), GL_STATIC_DRAW);
    
    //Vertices
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
    glEnableVertexAttribArray(0); // Active layout 0
    
    if (hasUV)
    {
        //UVs
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uv));
        glEnableVertexAttribArray(1); // Active layout 1 
    }
    
    if (hasNormals)
    {
        //Normal
        glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
        glEnableVertexAttribArray(2); // Active layout 2
    }
    
    
    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}


// Appelle cette fonction après chaque appel OpenGL important
void Mesh::CheckGLError(const char* location)
{
    GLenum err;
    while ((err = glGetError()) != GL_NO_ERROR)
    {
        std::string error;
        switch (err)
        {
        case GL_INVALID_ENUM:                  error = "INVALID_ENUM"; break;
        case GL_INVALID_VALUE:                 error = "INVALID_VALUE"; break;
        case GL_INVALID_OPERATION:             error = "INVALID_OPERATION"; break;
        case GL_OUT_OF_MEMORY:                 error = "OUT_OF_MEMORY"; break;
        case GL_INVALID_FRAMEBUFFER_OPERATION: error = "INVALID_FRAMEBUFFER_OPERATION"; break;
        default:                               error = "UNKNOWN"; break;
        }
        std::cerr << "\033[31m[OpenGL ERROR]\033[0m " << error << " at " << location << std::endl;
    }
}
