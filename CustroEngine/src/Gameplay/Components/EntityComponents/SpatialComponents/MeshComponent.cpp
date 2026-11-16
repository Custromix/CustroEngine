#include "MeshComponent.h"

MeshComponent::MeshComponent()
{
    Material* DefaultMaterial = Material::GetMaterialByName("DefaultMaterial");
    usableMaterial = DefaultMaterial;
}

MeshComponent::~MeshComponent()
{
    usableMaterial->UnSubscribe(this);
    
    usableMesh = nullptr;
    usableMaterial = nullptr;
    _Owner = nullptr;
}

void MeshComponent::SetMesh(Mesh* importedMesh)
{
    usableMesh = importedMesh;
    usableMaterial->RefreshGroup(this);
}

void MeshComponent::SetMaterial(Material& importedMaterial)
{
    usableMaterial->UnSubscribe(this);
    usableMaterial = &importedMaterial;
    usableMaterial->Subscribe(this);
}

void MeshComponent::SetActive(const bool NewActive)
{
    SpatialComponent::SetActive(NewActive);
    NewActive ? usableMaterial->RefreshGroup(this) : usableMaterial->UnSubscribe(this);
}

void MeshComponent::OnEnable()
{
    usableMaterial->RefreshGroup(this);
}

void MeshComponent::OnDisable()
{
    usableMaterial->UnSubscribe(this);
}

void MeshComponent::OnTransformChanged()
{
    if (usableMaterial)
        usableMaterial->OnComponentChanged(this);
}
