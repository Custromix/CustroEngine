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

void Renderer::Draw()
{
    for (int i = 0; i < MeshComponents.size(); ++i)
    {
        if (!MeshComponents[i])
            return;
        
        MeshComponents[i]->GetMesh()->Render();
    }
}
