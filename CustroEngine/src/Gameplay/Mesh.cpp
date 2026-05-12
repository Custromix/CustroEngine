#include "Mesh.h"

#include <iostream>
#include <glad/glad.h>

std::map<const String, Mesh*> Mesh::AllMeshesMap;

Mesh::Mesh(float vertices[], const String NewMeshName)
{

    ImportMesh(vertices);
    MeshName = NewMeshName;
    
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

void Mesh::ImportMesh(float vertices[])
{
    glGenVertexArrays(1, &VAO);
    
    glGenBuffers(1, &VBO);
    
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    
    glBindBuffer(GL_ARRAY_BUFFER, 0); 
    glBindVertexArray(0);
}
