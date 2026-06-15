#pragma once
#include "Gameplay/Mesh.h"
#include "Gameplay/Components/EntityComponents/SpatialComponent.h"
#include "Render/Material.h"


class MeshComponent : public SpatialComponent
{
public:
    MeshComponent();
    ~MeshComponent() override;
    
    void SetMesh(Mesh* importedMesh) { usableMesh = importedMesh; }
    void SetMaterial(Material importedMaterial);
    
    
    Mesh* GetMesh() { return usableMesh; }
    Material& GetMaterial() { return usableMaterial; }

private:
    Mesh* usableMesh = nullptr;
    
    Material usableMaterial;
};
