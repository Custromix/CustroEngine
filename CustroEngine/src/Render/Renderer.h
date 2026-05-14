#pragma once
#include "Gameplay/Components/MeshComponent.h"

class Renderer
{
public:
    
    static void Subscribe(MeshComponent* component);
    static void UnSubscribe(MeshComponent* component);
    
    static void Draw();
    
    
private:
    static std::vector<MeshComponent*> MeshComponents;
};
