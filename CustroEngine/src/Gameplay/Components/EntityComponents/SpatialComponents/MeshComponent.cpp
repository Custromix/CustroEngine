#include "MeshComponent.h"

#include "Render/Renderer.h"

MeshComponent::MeshComponent() : usableShader()
{
    Renderer::Get().Subscribe(this);
}

MeshComponent::~MeshComponent()
{
    Renderer::Get().UnSubscribe(this);
    
    usableMesh = nullptr;
    //usableShader = nullptr;
    _Owner = nullptr;
}
