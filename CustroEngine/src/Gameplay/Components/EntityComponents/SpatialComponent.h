#pragma once
#include "Gameplay/Components/EntityComponent.h"
#include "Render/Transform.h"

class SpatialComponent : public EntityComponent
{
public:
    SpatialComponent();
    virtual ~SpatialComponent() override = 0;
    
    Transform GetWorldTransform();

protected:
    Transform LocalTransform;
};