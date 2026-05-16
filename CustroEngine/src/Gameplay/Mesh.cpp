#include "Mesh.h"

#include <iostream>
#include <glad/glad.h>

std::map<const String, Mesh*> Mesh::AllMeshesMap;

Mesh::Mesh(float vertices[], size_t verticesSize, uint32 indices[], size_t indicesSize, const String NewMeshName)
{
    ImportMesh(vertices, verticesSize, indices, indicesSize);
    MeshName = NewMeshName;
    verticesCount = indicesSize/sizeof(uint32);
    
    std::cout << "verticesCount: " << verticesCount << std::endl;
    AllMeshesMap[MeshName] = this;
}

Mesh::~Mesh()
{
    AllMeshesMap.erase(MeshName);
}

Mesh* Mesh::GetMeshByName(const String MeshName)
{
    auto it = AllMeshesMap.find(MeshName);
    if (it != AllMeshesMap.end())
        return it->second;
    return nullptr;
}

void Mesh::Render()
{
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, verticesCount, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void Mesh::ImportMesh(float vertices[], size_t verticesSize, uint32 indices[], size_t indicesSize)
{
    
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &EBO);
    glGenBuffers(1, &VBO);
    
    if (VAO == 0 || VBO == 0 || EBO == 0)
    {
        std::cerr << "Erreur : VAO, VBO ou EBO non générés" << std::endl;
    }
    
    glBindVertexArray(VAO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    
    glEnableVertexAttribArray(0); // Active layout 0
    
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesSize, indices, GL_STATIC_DRAW);
    glBufferData(GL_ARRAY_BUFFER, verticesSize, vertices, GL_STATIC_DRAW);
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    
    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0); 
}
