#include "Transform.h"

#include "types.hpp"

const glm::vec3 Transform::VectorIdentity = glm::vec3(1.0f);
const glm::mat4 Transform::MatrixIdentity = glm::mat4(1.0f);

Transform::Transform(glm::vec3 Position, glm::vec3 Rotation, glm::vec3 Scale)
{
    this->Position = Position;
    this->Rotation = Rotation;
    this->Scale = Scale;
    UpdateMatrix();
}

Transform::~Transform()
{
    std::vector<Transform*> children = Childs;
    for (int i = 0; i < children.size(); ++i)
    {
        children[i]->SetParent(Parent);
    }
    
    Childs.clear();
    
    if (Parent)
        Parent->RemoveChild(this);
}

glm::vec3 Transform::GetWorldForward()
{
    glm::vec3 forward;
    forward.x = cos(glm::radians(GetWorldRotation().y)) * cos(glm::radians(GetWorldRotation().x));
    forward.y = sin(glm::radians(GetWorldRotation().x));
    forward.z = sin(glm::radians(GetWorldRotation().y)) * cos(glm::radians(GetWorldRotation().x));
    return glm::normalize(forward);
}

glm::vec3 Transform::GetLocalForward()
{
    glm::vec3 forward;
    forward.x = cos(glm::radians(Rotation.y)) * cos(glm::radians(Rotation.x));
    forward.y = sin(glm::radians(Rotation.x));
    forward.z = sin(glm::radians(Rotation.y)) * cos(glm::radians(Rotation.x));
    return glm::normalize(forward);
}

glm::vec3 Transform::GetWorldRight()
{
    return glm::normalize(glm::cross(GetWorldForward(), glm::vec3(0, 1, 0)));
}

glm::vec3 Transform::GetLocalRight()
{
    return glm::normalize(glm::cross(GetLocalForward(), glm::vec3(0, 1, 0)));
}

glm::vec3 Transform::GetWorldUp()
{
    return glm::vec3(0.0f, 1.0f, 0.0f);
}

glm::vec3 Transform::GetLocalUp()
{
    return glm::normalize(glm::cross(GetLocalForward(), glm::vec3(0, 1, 0)));
}

void Transform::SetWorldPosition(glm::vec3 position)
{
    if (!Parent)
    {
        SetLocalPosition(position);
        return;
    }
    
    glm::vec4 localPosFromWorld = glm::inverse(Parent->WorldModel) * glm::vec4(position, 1.0f);
    SetLocalPosition(localPosFromWorld);
}

void Transform::SetLocalPosition(glm::vec3 position)
{
    Position = position;
    UpdateMatrix();
}


void Transform::SetWorldRotation(glm::vec3 rotation)
{
    if (!Parent)
    {
        SetLocalRotation(rotation);
        return;
    }
    
    SetLocalRotation(rotation - Parent->GetWorldRotation());
}

void Transform::SetLocalRotation(glm::vec3 rotation)
{
    Rotation = rotation;
    UpdateMatrix();
}

void Transform::SetWorldScale(glm::vec3 scale)
{
    if (!Parent)
    {
        SetLocalScale(scale);
        return;
    }
    
    SetLocalScale(scale / Parent->GetWorldScale());
}

void Transform::SetLocalScale(glm::vec3 scale)
{
    this->Scale = scale;
    UpdateMatrix();
}

void Transform::RemoveChild(Transform* child)
{
    Childs.erase(std::remove(Childs.begin(), Childs.end(), child), Childs.end());
}

void Transform::SetParent(Transform* parent)
{
    if (Parent)
        Parent->RemoveChild(this);
    
    Parent = parent;
    
    if (parent)
        parent->AddChild(this);
    
    UpdateMatrix();
}

void Transform::UpdateMatrix()
{
    this->LocalModel = glm::mat4(1.0f);
    this->LocalModel = glm::translate(this->LocalModel, this->Position);
    this->LocalModel = glm::rotate(this->LocalModel, glm::radians(this->Rotation.x), glm::vec3(1.0, 0.0, 0.0));
    this->LocalModel = glm::rotate(this->LocalModel, glm::radians(this->Rotation.y), glm::vec3(0.0, 1.0, 0.0));
    this->LocalModel = glm::rotate(this->LocalModel, glm::radians(this->Rotation.z), glm::vec3(0.0, 0.0, 1.0));
    this->LocalModel = glm::scale(this->LocalModel, this->Scale);
    this->WorldModel = this->LocalModel;
    
    if (Parent)
        this->WorldModel = Parent->WorldModel * this->WorldModel;

    for (Transform* child : Childs)
    {
        child->UpdateMatrix();
    }
    
    if (OnChanged) OnChanged();
}
