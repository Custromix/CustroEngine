#include "EntityComponent.h"
#include "Gameplay/Entity.h"

EntityComponent::EntityComponent()
{
}

EntityComponent::~EntityComponent()
{
    _EntityOwner = nullptr;
}

void EntityComponent::SetOwner(GameObject* owner)
{
    Component::SetOwner(owner);
    _EntityOwner = static_cast<Entity*>(owner); 
}
