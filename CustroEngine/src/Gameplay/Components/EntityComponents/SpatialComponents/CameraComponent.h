#pragma once
#include "Gameplay/Components/EntityComponents/SpatialComponent.h"

class CameraComponent : public SpatialComponent
{
    
public:
    CameraComponent();
    ~CameraComponent() override;
    
    glm::vec3 cameraPos;
    glm::vec3 cameraFront;
    glm::vec3 cameraUp;
};
