#include "Component.h"

#include "Gameplay/GameObject.h"

Component::Component() : _Owner(nullptr)
{
}

Component::~Component()
{
}

bool Component::IsActive() const
{
    return isActive && (Owner() ? Owner()->IsActive() : false);
}
