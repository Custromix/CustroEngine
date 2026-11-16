#pragma once
#include <glm/vec3.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <functional>
#include <vector>

class Transform
{
    
public:
    Transform() : Position(0), Rotation(0), Scale(1) { UpdateMatrix(); } 
    Transform(glm::vec3 Position, glm::vec3 Rotation, glm::vec3 Scale);
    ~Transform();
    
    glm::vec3 GetWorldPosition()    {  return glm::vec3(WorldModel[3]);   }
    glm::vec3 GetLocalPosition()    {  return Position;  }
    
    glm::vec3 GetWorldRotation()    {  return Parent ? Parent->GetWorldRotation() + Rotation : Rotation;   }
    glm::vec3 GetLocalRotation()    {  return Rotation;  }
    
    glm::vec3 GetWorldScale() const
    {
        return glm::vec3(glm::length(glm::vec3(WorldModel[0])),
                         glm::length(glm::vec3(WorldModel[1])),
                         glm::length(glm::vec3(WorldModel[2])));
    }
    glm::vec3 GetLocalScale()       {   return Scale;    }
    
    const glm::mat4& GetWorldModel()       const {   return WorldModel;    }
    const glm::mat4& GetLocalModel()       const {   return LocalModel;    }
    
    glm::vec3 GetWorldForward();
    glm::vec3 GetLocalForward();
    
    glm::vec3 GetWorldRight();
    glm::vec3 GetLocalRight();
    
    glm::vec3 GetWorldUp();
    glm::vec3 GetLocalUp();
    
    
    void SetWorldPosition    (glm::vec3 position);
    void SetLocalPosition    (glm::vec3 position);
    void SetWorldRotation    (glm::vec3 rotation);
    void SetLocalRotation    (glm::vec3 rotation);
    void SetWorldScale       (glm::vec3 scale);
    void SetLocalScale       (glm::vec3 scale);
    
    void AddChild(Transform* child) { Childs.push_back(child); }
    void RemoveChild(Transform* child);
    void SetParent(Transform* parent);
    
    std::function<void()> OnChanged;
    
private:
    void UpdateMatrix();
    
public:
    const static glm::vec3 VectorIdentity;
    const static glm::mat4 MatrixIdentity;
    
private:
    glm::vec3 Position  =   glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 Rotation  =   glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 Scale     =   glm::vec3(1.0f, 1.0f, 1.0f);
    glm::mat4 WorldModel     =   glm::mat4(1.0f);
    glm::mat4 LocalModel     =   glm::mat4(1.0f);
    
    Transform* Parent = nullptr;
    std::vector<Transform*> Childs;
};
