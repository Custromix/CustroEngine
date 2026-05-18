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
    
    void Init();
    
    void Subscribe(MeshComponent* component);
    void UnSubscribe(MeshComponent* component);
    
    
    void InjectShaderCode(String shaderCode);
    uint32 CreateShaderPass(GLuint program, const char* PipelineShaderCode);
    uint32 CreateShaderPass(GLuint program, const char* PipelineShaderCode, const char* CustomShaderCode);
    
    
    void Draw();
    
    // Supprimer la copie
    Renderer(const Renderer&) = delete;
    Renderer& operator=(const Renderer&) = delete;
    
private:
    Renderer() {}
    
    uint32 ProgramId = 0;
    
    std::vector<MeshComponent*> MeshComponents;
    
    Shader* VertexShader = nullptr;
    Shader* FragmentShader = nullptr;
    
    glm::mat4 view = glm::mat4(1.0f);
    glm::mat4 projection = glm::mat4(1.0f);
};
