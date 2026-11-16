#pragma once
#include "Component.h"

class Entity;

class EntityComponent : public Component
{
    
public:
    EntityComponent();
    virtual ~EntityComponent() override = 0;
    
    void SetOwner(GameObject* owner) override;
    Entity* Owner() const { return _EntityOwner; }
    
protected:
    Entity* _EntityOwner = nullptr;
    
};
