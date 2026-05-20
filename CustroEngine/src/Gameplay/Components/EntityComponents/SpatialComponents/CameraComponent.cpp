#include "CameraComponent.h"

CameraComponent::CameraComponent()
{
    cameraPos   = glm::vec3(0.0f, 0.0f,  3.0f);
    cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
    cameraUp    = glm::vec3(0.0f, 1.0f,  0.0f);
}

CameraComponent::~CameraComponent()
{
}
