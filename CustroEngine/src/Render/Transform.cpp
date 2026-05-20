#include "Transform.h"

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
}

void Transform::SetPosition(glm::vec3 position)
{
    this->Position = position;
    UpdateMatrix();
}

void Transform::SetRotation(glm::vec3 rotation)
{
    this->Rotation = rotation;
    UpdateMatrix();
}

void Transform::SetScale(glm::vec3 scale)
{
    this->Scale = scale;
    UpdateMatrix();
}

void Transform::UpdateMatrix()
{
    this->Model = glm::mat4(1.0f);
    this->Model = glm::translate(this->Model, this->Position);
    this->Model = glm::rotate(this->Model, glm::radians(this->Rotation.x), glm::vec3(1.0, 0.0, 0.0));
    this->Model = glm::rotate(this->Model, glm::radians(this->Rotation.y), glm::vec3(0.0, 1.0, 0.0));
    this->Model = glm::rotate(this->Model, glm::radians(this->Rotation.z), glm::vec3(0.0, 0.0, 1.0));
    this->Model = glm::scale(this->Model, this->Scale);
}
