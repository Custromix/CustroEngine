#include "MeshComponent.h"

#include "Render/Renderer.h"

MeshComponent::MeshComponent()
{
    Renderer::Get().Subscribe(this);
}

MeshComponent::~MeshComponent()
{
    Renderer::Get().UnSubscribe(this);
    
    usableMesh = nullptr;
    _Owner = nullptr;
}
