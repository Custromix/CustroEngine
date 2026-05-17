#pragma once
#include "Shader.h"
#include "Gameplay/Components/MeshComponent.h"

class Renderer
{
public:
    
    static Renderer& Get()
    {
        static Renderer instance;
        return instance;
    }
    
    void Init(Shader* shader);
    
    void Subscribe(MeshComponent* component);
    void UnSubscribe(MeshComponent* component);
    
    void Draw();
    
    // Supprimer la copie
    Renderer(const Renderer&) = delete;
    Renderer& operator=(const Renderer&) = delete;
    
private:
    Renderer() {}
    
    std::vector<MeshComponent*> MeshComponents;
    
    Shader* RenderShader = nullptr;
};
