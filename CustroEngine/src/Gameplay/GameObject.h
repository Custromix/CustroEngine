#pragma once
#include <vector>
#include "Components/Component.h"


class CustroEngine;

class GameObject
{
    friend class CustroEngine;
    friend class Scene;
    
protected:
    virtual void Construct() {}
    
    template <typename T>
    T* AddComponent()
    {
        T* comp = new T();
        Components.push_back(comp);
        return comp;
    }
    
private:
    static void SetEngine(CustroEngine* Engine) { CustroEngineInstance = Engine; }
    
public:
    GameObject();
    virtual ~GameObject();
    
    virtual void Start() = 0;
    
    virtual void Update(float deltaTime) = 0;
    
protected:
    std::vector<Component*> Components;
    
    static CustroEngine* CustroEngineInstance;
    
    
};
