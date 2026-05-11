#pragma once
#include "Component.h"

class EntityComponent : public Component
{

public:
    EntityComponent();
    ~EntityComponent() override;
    
public:
    virtual void Start();
    virtual void Update(float deltaTime);
    
};
