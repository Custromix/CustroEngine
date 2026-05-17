#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Shader.h"
#include "Gameplay/Mesh.h"
#include "Gameplay/Scene.h"
#include "Render/Renderer.h"
#include "Render/Texture.h"


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
    
    Texture* ImportTexture(String TexturePath);
    
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
    
    std::vector<Texture*> GarbagedTexture;
    
    std::vector<Scene*> GarbagedScene;

public:
    static const uint16 WINDOW_WIDTH = 800;
    static const uint16 WINDOW_HEIGHT = 600;
    
};
