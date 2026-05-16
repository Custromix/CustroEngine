#include "Renderer.h"

std::vector<MeshComponent*> Renderer::MeshComponents;

void Renderer::Subscribe(MeshComponent* component)
{
    MeshComponents.push_back(component);
}

void Renderer::UnSubscribe(MeshComponent* component)
{
    MeshComponents.erase(std::remove(MeshComponents.begin(), MeshComponents.end(), component), MeshComponents.end());
}

void Renderer::Draw(Shader* shader)
{
    for (int i = 0; i < MeshComponents.size(); ++i)
    {
        if (!MeshComponents[i])
            return;
        
        //if (MeshComponents[i]->Owner()->GetTransform())
            //std::cout << "Transform SET " << MeshComponents[i]->Owner()->GetTransform()->GetPosition().x << std::endl;
        
        shader->setMatrix4("model", MeshComponents[i]->Owner()->GetTransform()->GetModel());
        MeshComponents[i]->GetMesh()->Render();
    }
}
