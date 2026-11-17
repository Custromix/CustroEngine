#include "Mesh.h"

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Render/Vertex.h"

uint32 Mesh::NbMeshes = 0;
std::map<const String, Mesh*> Mesh::AllMeshesMap;

Mesh::Mesh(const MeshData& NewMeshData, const String NewMeshName)
{
    MyMeshData = NewMeshData;
    //float verticesData[], size_t verticesSize, float uv[], size_t uvSize, float normals[], size_t normalsSize, uint32 indices[], size_t indicesSize,
    NbMeshes++;
    MeshID = NbMeshes;
    MeshName = NewMeshName;
    trianglesCount = NewMeshData.Indices.size()/3;
    
    std::cout << "verticesCount: " << MyMeshData.Vertices.size() << std::endl;
    std::cout << "indicesCount: " << trianglesCount << std::endl;
    
    AllMeshesMap[MeshName] = this;
    
    ImportMesh();
}

Mesh::~Mesh()
{
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
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
    glDrawElements(GL_TRIANGLES, GetTotalDrawingVertices(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void Mesh::ConfigureVAO(uint32 vao)
{
    glBindVertexArray(vao);
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    
    //Vertices
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
    glEnableVertexAttribArray(0); // Active layout 0
    
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uv));
    glEnableVertexAttribArray(1); // Active layout 1 
    
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
    glEnableVertexAttribArray(2); // Active layout 2
    
    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Mesh::ImportMesh()
{
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &EBO);
    glGenBuffers(1, &VBO);
    
    if (VAO == 0 || EBO == 0 || VBO == 0)
    {
        std::cerr << "Erreur : VAO, VBO ou EBO non générés" << std::endl;
    }
    
    std::cout << "verticesCount = " << GetTotalDrawingVertices() << std::endl;
    std::cout << "Vertices.size() = " << MyMeshData.Vertices.size() << std::endl;
    
    glBindVertexArray(VAO);
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, MyMeshData.Indices.size() * sizeof(uint32), MyMeshData.Indices.data(), GL_STATIC_DRAW);
    
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER,  sizeof(Vertex) * MyMeshData.Vertices.size(),  MyMeshData.Vertices.data(), GL_STATIC_DRAW);
    
    ConfigureVAO(VAO);
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
