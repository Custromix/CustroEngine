#include "GameObject.h"

#include <iostream>
#include <ostream>
#include <string>

#include "types.hpp"

CustroEngine* GameObject::CustroEngineInstance = nullptr;
int64_t GameObject::GameObjectCounter = 0;
GameObject::GameObject()
{
    GameObjectCounter++;
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