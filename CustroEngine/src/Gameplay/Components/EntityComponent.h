#pragma once
#include "Component.h"

class Entity;

class EntityComponent : public Component
{

public:
    EntityComponent();
    ~EntityComponent() override;
    
    Entity* Owner() const { return _EntityOwner; }

    void SetOwner(GameObject* owner) override;
    
    
public:
    virtual void Start();
    virtual void Update(float deltaTime);
    
private:
    Entity* _EntityOwner = nullptr;
    
};
