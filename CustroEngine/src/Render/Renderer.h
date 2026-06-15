#pragma once
#include "Shader.h"
#include "Gameplay/Components/EntityComponents/SpatialComponents/MeshComponent.h"

class Renderer
{
public:
    
    static Renderer& Get()
    {
        static Renderer instance;
        return instance;
    }
    
    ~Renderer();
    
    void Init();
    
    void UnSubscribe(Shader* shader);
    
    Shader* CreateShader(const String ShaderPath, const String MeshName);
    
    void InjectShaderCode(String shaderCode);
    uint32 CreateShaderPass(GLuint program, const char* PipelineShaderCode);
    uint32 CreateShaderPass(GLuint program, const char* PipelineShaderCode, const char* CustomShaderCode);
    
    void UpdateProjectionMatrix(uint32 FOV, uint32 width, uint32 height);
    void UpdateViewMatrix();
    
    void Render();
    
    // Supprimer la copie
    Renderer(const Renderer&) = delete;
    Renderer& operator=(const Renderer&) = delete;
    
private:
    Renderer() {}
    
    std::vector<Shader*> Shaders;
    
    Shader* VertexShader = nullptr;
    Shader* FragmentShader = nullptr;
    
    glm::mat4 view = glm::mat4(1.0f);
    glm::mat4 projection = glm::mat4(1.0f);
};