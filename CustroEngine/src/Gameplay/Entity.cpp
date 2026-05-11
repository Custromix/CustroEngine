#include "Entity.h"

void Entity::Construct(glm::vec3 Position, glm::vec3 Rotation, glm::vec3 Scale)
{
    transform = Transform(Position, Rotation, Scale);
}

Entity::Entity()
{
}

Entity::~Entity()
{
    for (int i = 0; i < EntityComponents.size(); i++)
    {
        delete EntityComponents[i];
        EntityComponents[i] = nullptr;
    }
}

void Entity::Start()
{
    for (int i = 0; i < EntityComponents.size(); i++)
    {
        EntityComponents[i]->Start();
    }
}

void Entity::Update(float deltaTime)
{
    for (int i = 0; i < EntityComponents.size(); i++)
    {
        EntityComponents[i]->Update(deltaTime);
    }
}


