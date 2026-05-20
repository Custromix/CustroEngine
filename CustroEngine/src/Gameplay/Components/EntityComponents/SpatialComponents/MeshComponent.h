#pragma once
#include "Gameplay/Mesh.h"
#include "Gameplay/Components/EntityComponents/SpatialComponent.h"
#include "Render/Shader.h"


class MeshComponent : public SpatialComponent
{
public:
    MeshComponent();
    ~MeshComponent() override;
    
    void SetMesh(Mesh* importedMesh) { usableMesh = importedMesh; }
    void SetShader(Shader importedShader) { usableShader = importedShader; }
    
    
    Mesh* GetMesh() { return usableMesh; }
    Shader& GetShader() { return usableShader; }

private:
    Mesh* usableMesh = nullptr;
    
    Shader usableShader;
};
