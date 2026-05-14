#include "MeshComponent.h"

#include "Render/Renderer.h"

MeshComponent::MeshComponent()
{
    Renderer::Subscribe(this);
}

MeshComponent::~MeshComponent()
{
    Renderer::UnSubscribe(this);
    
    usableMesh = nullptr;
    Owner = nullptr;
}
