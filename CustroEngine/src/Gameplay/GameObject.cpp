#include "GameObject.h"

#include <iostream>
#include <ostream>

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

void GameObject::StartEngineClass()
{
    std::cout << "\033[33m" << "GameObject::" << Name << "::Initialized" << "\033[0m" << std::endl;
    Start();
}

void GameObject::Construct()
{
    Name = typeid(*this).name();
}
