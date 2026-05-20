#pragma once
#include <glm/vec3.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Transform
{
    
public:
    Transform() : Position(0), Rotation(0), Scale(1) { UpdateMatrix(); } 
    Transform(glm::vec3 Position, glm::vec3 Rotation, glm::vec3 Scale);
    ~Transform();
    
    glm::vec3 GetPosition()     {  return Position;  }
    glm::vec3 GetRotation()     {  return Rotation;  }
    glm::vec3 GetScale()        {   return Scale;    }
    glm::mat4 GetModel()        {   return Model;    }
    
    
    void SetPosition    (glm::vec3 Position);
    void SetRotation    (glm::vec3 rotation);
    void SetScale       (glm::vec3 scale);
    
private:
    void UpdateMatrix();
    
public:
    const static glm::vec3 VectorIdentity;
    const static glm::mat4 MatrixIdentity;
    
private:
    glm::vec3 Position  =   glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 Rotation  =   glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 Scale     =   glm::vec3(1.0f, 1.0f, 1.0f);
    glm::mat4 Model     =   glm::mat4(1.0f);
};
