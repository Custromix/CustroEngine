#pragma once
#include <glm/matrix.hpp>

#include "GameObject.h"
#include "Components/EntityComponents/BehaviourComponent.h"
#include "Components/EntityComponents/SpatialComponent.h"
#include "Render/Transform.h"


class Entity: public GameObject
{
    friend class Scene;

public:
    Entity();
    ~Entity() override;
    
private:
    virtual void Construct(const glm::vec3 Position, const glm::vec3 Rotation = glm::vec3(0.f, 0.f, 0.f), const glm::vec3 Scale = glm::vec3(1.f, 1.f, 1.f)) final;
    
protected:
    template <typename T>
    T* AddComponent()
    {
        T* comp = new T();
        comp->SetOwner(this);
        
        Components.push_back(comp);
        
        if constexpr (std::is_base_of<BehaviourComponent, T>::value)
            BehaviourComponents.push_back(comp);
        
        if constexpr (std::is_base_of<SpatialComponent, T>::value)
            SpatialComponents.push_back(comp);
        
        return comp;
    }

public:
    void Start() override;
    void Update(float deltaTime) override;
    
    Transform* GetTransform(){ return &transform; }

private:
    Transform transform;
    
    std::vector<BehaviourComponent*> BehaviourComponents;
    std::vector<SpatialComponent*> SpatialComponents;
};
