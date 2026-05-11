#pragma once
#include "GameObject.h"
#include "Components/EntityComponent.h"
#include "Components/Transform.h"


class Entity: public GameObject
{
    friend class Scene;

public:
    Entity();
    ~Entity() override;
    
private:
    virtual void Construct(glm::vec3 Position, glm::vec3 Rotation = glm::vec3(0.f, 0.f, 0.f), glm::vec3 Scale = glm::vec3(1.f, 1.f, 1.f)) final;
    
protected:
    template <typename T>
    T* AddComponent()
    {
        T* comp = new T();
        
        if constexpr (std::is_base_of<EntityComponent, T>::value)
            EntityComponents.push_back(comp);
        else 
            Components.push_back(comp);
        
        return comp;
    }

public:
    void Start() override;
    void Update(float deltaTime) override;
    
    Transform* GetTransform(){ return &transform; }

private:
    Transform transform;
    
    std::vector<EntityComponent*> EntityComponents;
};
