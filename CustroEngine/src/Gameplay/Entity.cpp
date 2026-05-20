#include "Entity.h"

void Entity::Construct(const glm::vec3 Position, const glm::vec3 Rotation, const glm::vec3 Scale)
{
    GameObject::Construct();
    transform = Transform(Position, Rotation, Scale);
}

Entity::Entity()
{
    
}

Entity::~Entity()
{
    BehaviourComponents.clear();
    SpatialComponents.clear();
}

void Entity::Start()
{
    for (int i = 0; i < BehaviourComponents.size(); i++)
    {
        BehaviourComponents[i]->Start();
    }
}

void Entity::Update(float deltaTime)
{
    for (int i = 0; i < BehaviourComponents.size(); i++)
    {
        BehaviourComponents[i]->Update(deltaTime);
    }
}


