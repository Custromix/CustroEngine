#include "Renderer.h"

#include "CustroEngine.h"

void Renderer::Init(Shader* shader)
{
    if (!shader)
        return;
    
    RenderShader = shader;
    glm::mat4 view = glm::mat4(1.0f);
    view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f)); 
        
    glm::mat4 projection = glm::mat4(1.0f);
    projection = glm::perspectiveFov(glm::radians(50.0f), static_cast<float>(CustroEngine::WINDOW_WIDTH), static_cast<float>(CustroEngine::WINDOW_HEIGHT), 0.1f, 100.0f);
    
    RenderShader->setMatrix4("view", view);
    RenderShader->setMatrix4("projection", projection);
}

void Renderer::Subscribe(MeshComponent* component)
{
    MeshComponents.push_back(component);
}

void Renderer::UnSubscribe(MeshComponent* component)
{
    MeshComponents.erase(std::remove(MeshComponents.begin(), MeshComponents.end(), component), MeshComponents.end());
}

void Renderer::Draw()
{
    for (int i = 0; i < MeshComponents.size(); ++i)
    {
        if (!MeshComponents[i])
            return;
        
        RenderShader->setMatrix4("model", MeshComponents[i]->Owner()->GetTransform()->GetModel());
        
        MeshComponents[i]->GetMesh()->Render();
    }
}

