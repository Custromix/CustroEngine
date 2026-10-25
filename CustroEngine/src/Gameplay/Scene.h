#pragma once
#include <vector>
#include <concepts>

#include "GameObject.h"
#include "Components/EntityComponents/SpatialComponents/MeshComponent.h"

template <typename T>
concept SpawnableType = std::is_base_of_v<GameObject, T>;

class Scene
{
    friend class CustroEngine;

private:
    std::vector<GameObject*> PendingGameObjects;
    std::vector<GameObject*> AliveGameObjects;
    
    //std::vector<MeshComponent*> &MeshComponents;

public:
    Scene();
    ~Scene();

    template<SpawnableType T, typename... Args>
    
    T* Spawn(Args... args)
    {
        T* obj = new T();
        obj->Construct(std::forward<Args>(args)...);
        PendingGameObjects.push_back(obj);
        return obj;
    }
    
    const std::vector<GameObject*>& GetPendingGameObjects() const{ return PendingGameObjects; }
    const std::vector<GameObject*>& GetAliveGameObjects() const{ return AliveGameObjects; }
    
    //std::vector<MeshComponent*> GetMeshComponents() { return MeshComponents; }

private:
    void MovePendingGOToAlive();
    
};
