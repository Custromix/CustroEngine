#include "EntityComponent.h"

#include "Gameplay/Entity.h"

EntityComponent::EntityComponent()
{
    
}

EntityComponent::~EntityComponent()
{
}

void EntityComponent::SetOwner(GameObject* owner)
{
    Component::SetOwner(owner);
    _EntityOwner = static_cast<Entity*>(owner); 
}

void EntityComponent::Start()
{
}

void EntityComponent::Update(float deltaTime)
{
}
