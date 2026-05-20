#pragma once
#include <vector>
#include "Components/Component.h"
#include "utils/String.h"


class CustroEngine;

using namespace Engine;

class GameObject
{
    friend class CustroEngine;
    friend class Scene;
    
public:
    GameObject();
    virtual ~GameObject();
    
    virtual void StartEngineClass();
    
    virtual void Start() = 0;
    
    virtual void Update(float deltaTime) = 0;
    
    String GetName() const { return Name; }
    
protected:
    virtual void Construct();
    
    template <typename T>
    T* AddComponent()
    {
        T* comp = new T();
        comp->SetOwner(this);
        Components.push_back(comp);
        return comp;
    }
    
private:
    static void SetEngine(CustroEngine* Engine) { CustroEngineInstance = Engine; }

    
protected:
    std::vector<Component*> Components;
    
    static CustroEngine* CustroEngineInstance;
    
private:
    String Name = String("");
    
    
};
