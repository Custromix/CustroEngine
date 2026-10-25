#include "Scene.h"

#include "types.hpp"

Scene::Scene()
{
}

Scene::~Scene()
{
    for (Engine::int32 i = 0; i < PendingGameObjects.size() ; i++)
    {
        delete PendingGameObjects[i];
        PendingGameObjects[i] = nullptr;
    }
    
    for (Engine::int32 i = 0; i < AliveGameObjects.size() ; i++)
    {
        delete AliveGameObjects[i];
        AliveGameObjects[i] = nullptr;
    }
}

void Scene::MovePendingGOToAlive()
{
    AliveGameObjects.insert(AliveGameObjects.end(), std::make_move_iterator(PendingGameObjects.begin()), std::make_move_iterator(PendingGameObjects.end()));
    PendingGameObjects.clear();
}
