#pragma once
#include <vector>
#include <concepts>

#include "GameObject.h"

template <typename T>
concept SpawnableType = std::is_base_of_v<GameObject, T>;

class Scene
{

private:
    std::vector<GameObject*> GameObjects;

public:
    Scene();
    ~Scene();

    template<SpawnableType T, typename... Args>
    
    T* Spawn(Args... args)
    {
        T* obj = new T();
        obj->Construct(std::forward<Args>(args)...);
        GameObjects.push_back(obj);
        return obj;
    }
    
    std::vector<GameObject*> GetGameObjects() { return GameObjects; }

private:

    
};
