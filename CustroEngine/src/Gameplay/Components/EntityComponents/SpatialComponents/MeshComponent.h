#pragma once
#include "Gameplay/Mesh.h"
#include "Gameplay/Components/EntityComponents/SpatialComponent.h"
#include "Render/Material.h"

using namespace Engine;

class MeshComponent : public SpatialComponent
{
public:
    MeshComponent();
    ~MeshComponent() override;
    
    void SetMesh(Mesh* importedMesh);
    void SetMaterial(Material& importedMaterial);
    
    Mesh* GetMesh() { return usableMesh; }
    Material& GetMaterial() { return *usableMaterial; }
    
    void SetActive(const bool NewActive) override;
    void OnEnable() override;
    void OnDisable() override;
    
    void OnTransformChanged() override;
    
public:
    uint32 indexInGroup = -1;

private:
    Mesh* usableMesh = nullptr;
    
    Material* usableMaterial = nullptr;
};
