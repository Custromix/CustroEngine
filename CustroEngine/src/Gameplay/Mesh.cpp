#include "Mesh.h"

#include <iostream>
#include <glad/glad.h>

std::vector<Mesh*> Mesh::AllMeshes;
std::map<const char*, Mesh*> Mesh::AllMeshesMap;

Mesh::Mesh(float vertices[], const char* NewMeshName)
{

    ImportMesh(vertices);
    MeshName = NewMeshName;
    AllMeshes.push_back(this);
    AllMeshesIndex = AllMeshes.size()-1;
    
    AllMeshesMap["MeshName"] = this;
}

Mesh::~Mesh()
{
    AllMeshes.erase(std::remove(AllMeshes.begin(), AllMeshes.end(), this), AllMeshes.end());
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
