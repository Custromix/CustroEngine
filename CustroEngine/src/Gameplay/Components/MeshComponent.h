#pragma once
#include <vector>

#include "Component.h"
#include "Gameplay/Entity.h"
#include "Gameplay/Mesh.h"
#include "Render/Shader.h"


class MeshComponent : public EntityComponent
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
