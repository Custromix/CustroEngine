#include "GameObject.h"

#include "types.hpp"

CustroEngine* GameObject::CustroEngineInstance = nullptr;
GameObject::GameObject()
{
}

GameObject::~GameObject()
{
    for (Engine::int32 i = 0; i < Components.size(); ++i)
    {
        delete Components[i];
        Components[i] = nullptr;
    }
}
