#include "Scene.h"

#include "types.hpp"

Scene::Scene()
{
}

Scene::~Scene()
{
    for (Engine::int32 i = 0; i < GameObjects.size() ; i++)
    {
        delete GameObjects[i];
        GameObjects[i] = nullptr;
    }
        
}
