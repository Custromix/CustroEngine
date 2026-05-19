#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Gameplay/Mesh.h"
#include "Gameplay/Scene.h"
#include "Render/Renderer.h"
#include "Render/Texture.h"


class CustroEngine
{

public:
    CustroEngine();
    ~CustroEngine();
    
    void Lunch();
    
    void SetCurrentScene(Scene* Scene);
    
    //Mesh* ImportMesh(char path, const char* MeshName);
    //TODO: Supprimer cette fonction quand on aura fait le parser
    Mesh* ImportMesh(float* vertices, size_t verticesSize, float uv[], size_t uvSize, float normals[], size_t normalsSize, uint32 faces[], size_t facesSize, const String MeshName);
    
    Shader* ImportShader(const String ShaderPath, const String MeshName);
    
    Texture* ImportTexture(const String TexturePath, String TextureName = "");
    
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
    
    std::vector<Shader*> GarbagedShaders;
    
    std::vector<Texture*> GarbagedTexture;
    
    std::vector<Scene*> GarbagedScene;

public:
    static const uint16 WINDOW_WIDTH = 800;
    static const uint16 WINDOW_HEIGHT = 600;
    
};
