#include "GameObject.h"

#include <iostream>
#include <ostream>
#include <string>

#include "types.hpp"

CustroEngine* GameObject::CustroEngineInstance = nullptr;
uint64 GameObject::GameObjectCounter = 0;
GameObject::GameObject()
{
    GameObjectCounter++;
}

void GameObject::SetActive(const bool NewActive)
{
    isActive = NewActive;
    if (isActive)
    {
        for (Component* comp : Components)
        {
            comp->OnEnable();
        }
    }else
    {
        for (Component* comp : Components)
        {
            comp->OnDisable();
        }
    }
}

void GameObject::Construct()
{
    Name = typeid(*this).name();
    Name = Name + "_" + std::to_string(GameObjectCounter).c_str();
}

void GameObject::StartEngineClass()
{
    std::cout << "\033[33m" << "GameObject::" << Name << "::Initialized" << "\033[0m" << std::endl;
    Start();
}

void GameObject::Destroy()
{
    isDestroyNextFrame = true;
    SetActive(false);
}

GameObject::~GameObject()
{
    for (Engine::int32 i = 0; i < Components.size(); ++i)
    {
        delete Components[i];
        Components[i] = nullptr;
    }
}