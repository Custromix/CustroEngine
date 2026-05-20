#pragma once
#include "Gameplay/Components/EntityComponent.h"

class BehaviourComponent : public EntityComponent
{

public:
    BehaviourComponent();
    ~BehaviourComponent() override = 0;

public:
    virtual void Start();
    virtual void Update(float deltaTime);
    
    
};
