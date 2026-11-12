#include "MeshComponent.h"

#include "Render/Renderer.h"

MeshComponent::MeshComponent() : usableMaterial(new Shader(), "")
{
    usableMaterial.GetShader().Subscribe(this);
}

MeshComponent::~MeshComponent()
{
    usableMaterial.GetShader().UnSubscribe(this);
    
    usableMesh = nullptr;
    //usableShader = nullptr;
    _Owner = nullptr;
}

void MeshComponent::SetMaterial(Material importedMaterial)
{
    usableMaterial.GetShader().UnSubscribe(this);
    usableMaterial = importedMaterial;
    usableMaterial.GetShader().Subscribe(this);
}

void MeshComponent::SetActive(const bool NewActive)
{
    SpatialComponent::SetActive(NewActive);
    NewActive ? usableMaterial.GetShader().Subscribe(this) : usableMaterial.GetShader().UnSubscribe(this);
}
