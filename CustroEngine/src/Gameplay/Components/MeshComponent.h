#pragma once
#include <vector>

#include "Component.h"
#include "Gameplay/Mesh.h"

class MeshComponent : public Component
{
public:
    MeshComponent();
    ~MeshComponent() override;
    
    void SetMesh(Mesh* importedMesh) { usableMesh = importedMesh; }
    
    Mesh* GetMesh() const { return usableMesh; }
    
private:
    Mesh* usableMesh = nullptr;
    
    Transform* EntityTransform;
    
};