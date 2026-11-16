#pragma once
#include "Gameplay/Components/EntityComponent.h"
#include "Render/Transform.h"

class SpatialComponent : public EntityComponent
{
public:
    SpatialComponent();
    virtual ~SpatialComponent() override = 0;
    
    void SetOwner(GameObject* owner) final;

    virtual void OnTransformChanged() {}
    
    Transform& GetTransform() { return ComponentTransform; }
    
protected:
    Transform ComponentTransform;
};