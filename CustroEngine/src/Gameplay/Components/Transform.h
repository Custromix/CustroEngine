#pragma once
#include <glm/vec3.hpp>

#include "Component.h"

class Transform : public Component
{
    
public:
    Transform() : Position(0), Rotation(0), Scale(1) {} 
    Transform(glm::vec3 Position, glm::vec3 Rotation, glm::vec3 Scale);
    ~Transform() override;


    glm::vec3 GetPosition()  {  return Position;  }
    glm::vec3 GetRotation()  {  return Rotation;  }
    glm::vec3 GetScale()     {   return Scale;    }
    
private:
    glm::vec3 Position;
    glm::vec3 Rotation;
    glm::vec3 Scale;
};
