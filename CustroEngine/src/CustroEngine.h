#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Shader.h"
#include "Gameplay/Mesh.h"
#include "Gameplay/Scene.h"
#include "Gameplay/Components/MeshComponent.h"


class CustroEngine
{

public:
    CustroEngine();
    ~CustroEngine();
    
    void Init();
    
    void Lunch();
    
    void SetCurrentScene(Scene* Scene);
    
    //Mesh* ImportMesh(char path, const char* MeshName);
    //TODO: Supprimer cette fonction quand on aura fait le parser
    Mesh* ImportMesh(float* vertices, size_t verticesSize, uint32 indices[], size_t indicesSize, const char* MeshName);
    
    Mesh* GetMesh(const String MeshName);
    
    Scene* CreateScene();
    
private:
    void PreStart();
    void Start();
    void Update();
    
private:
    GLFWwindow* window = nullptr;
    
    Scene* currentScene = nullptr;
    
    Shader* shader = nullptr;
    
    std::vector<Mesh*> GarbagedMeshes;
    
    std::vector<Scene*> GarbagedScene;

private:
    const unsigned int WINDOW_WIDTH = 800;
    const unsigned int WINDOW_HEIGHT = 600;
    
};
