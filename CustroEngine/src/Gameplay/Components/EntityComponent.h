#pragma once
#include "Component.h"

class Entity;

class EntityComponent : public Component
{
    
public:
    EntityComponent();
    virtual ~EntityComponent() override = 0;
    
    void SetOwner(GameObject* owner) final;
    Entity* Owner() const { return _EntityOwner; }
    
private:
    Entity* _EntityOwner = nullptr;
    
};
