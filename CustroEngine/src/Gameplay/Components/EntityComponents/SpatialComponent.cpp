#include "SpatialComponent.h"

#include "Gameplay/Entity.h"

SpatialComponent::SpatialComponent()
{
    LocalTransform.SetPosition(glm::vec3(0.0f, 0.0f, 0.0f));
    LocalTransform.SetRotation(glm::vec3(0.0f, 0.0f, 0.0f));
    LocalTransform.SetScale(glm::vec3(1.0f, 1.0f, 1.0f));
}

SpatialComponent::~SpatialComponent()
{
}

Transform SpatialComponent::GetWorldTransform()
{
    Transform* parentTransform = Owner()->GetTransform();
    
    Transform World;
    World.SetPosition(parentTransform->GetPosition() + LocalTransform.GetPosition());
    World.SetRotation(parentTransform->GetRotation() + LocalTransform.GetRotation());
    World.SetScale(parentTransform->GetScale() * LocalTransform.GetScale());
    
    return World;
}
