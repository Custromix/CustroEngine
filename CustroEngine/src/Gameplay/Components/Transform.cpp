#include "Transform.h"

Transform::Transform(glm::vec3 Position, glm::vec3 Rotation, glm::vec3 Scale)
{
    this->Position = Position;
    this->Rotation = Rotation;
    this->Scale = Scale;
}

Transform::~Transform()
{
}
