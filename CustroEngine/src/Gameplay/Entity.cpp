#include "Entity.h"

void Entity::Construct(glm::vec3 Position, glm::vec3 Rotation, glm::vec3 Scale)
{
    GameObject::Construct();
    transform = Transform(Position, Rotation, Scale);
}

Entity::Entity()
{
    std::cout << "\033[33m" << "CustroEngine::INITIALIZED" << "\033[0m" << std::endl;
}

Entity::~Entity()
{
    for (int i = 0; i < EntityComponents.size(); i++)
    {
        delete EntityComponents[i];
        EntityComponents[i] = nullptr;
    }
    
    /*
    for (int i = 0; i < Components.size(); i++)
    {
        delete Components[i];
        Components[i] = nullptr;
    }*/
    
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


