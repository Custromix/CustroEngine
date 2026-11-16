#include "SpatialComponent.h"

#include "Gameplay/Entity.h"

SpatialComponent::SpatialComponent()
{
    ComponentTransform.OnChanged = [this]() { OnTransformChanged(); };
}

SpatialComponent::~SpatialComponent()
{
}

void SpatialComponent::SetOwner(GameObject* owner)
{
    EntityComponent::SetOwner(owner);
    ComponentTransform.SetParent(_EntityOwner->GetTransform());
}
