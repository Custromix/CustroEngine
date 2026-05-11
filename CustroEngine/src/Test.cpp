#define _CRTDBG_MAP_ALLOC
#include <cstdlib>
#include <crtdbg.h>
#ifdef _DEBUG
#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)
#endif

#include "CustroEngine.h"
#include "Shader.h"
#include "Gameplay/Entity.h"
#include "Gameplay/Scene.h"
#include "Gameplay/Components/MeshComponent.h"



class BasicSystem : public EntityComponent
{
    
public:
    BasicSystem(){}
    ~BasicSystem() override {}
    
    void Start() override {}
    void Update(float deltaTime) override {}
    
};


class GameManager : public GameObject
{
public:
    GameManager()
    {
        
    }
    
    ~GameManager() override
    {
        
    }
    
    void Start() override
    {
        
    }
    
    void Update(float deltaTime) override
    {
        
    }
    
};

class ObjectQuelconque : public Entity
{
    
private:
    MeshComponent* MeshComp;
    BasicSystem* BasicSystem;
    
public:
    ObjectQuelconque()
    {
        MeshComp = AddComponent<MeshComponent>();
        BasicSystem = AddComponent<class BasicSystem>();
    }
    
    ~ObjectQuelconque() override
    {
        //delete MeshComp;
        //delete BasicSystem;
    }
    
    void Start() override
    {
        //std::cout << "Position = " + std::to_string(GetTransform()->GetPosition().x)  << std::endl;
        MeshComp->SetMesh(Mesh::GetMeshByName("triangle"));
    }
    
    void Update(float deltaTime) override
    {
        //std::cout << "DeltaTime = " + std::to_string(deltaTime)  << std::endl;
    }

};

int main() {
    //_CrtSetBreakAlloc(493); // le numéro de la fuite

    float vertices[] = {
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.0f,  0.5f, 0.0f
    };
    
    
    
    
    
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    
    CustroEngine* Engine = new CustroEngine();
    
    Engine->Init();
    
    Scene MyScene = Scene();
    
    Engine->SetCurrentScene(&MyScene);
    
    GameManager* MyGameManager = MyScene.Spawn<class GameManager>();
    
    ObjectQuelconque* Cube = MyScene.Spawn<class ObjectQuelconque>(glm::vec3(9.f, 0.0f, 0.0f));
    
    Engine->ImportMesh(vertices, "Triangle");
    
    
    // Code du jeu

    Engine->Lunch();
    
    delete Engine;
    
    
    _CrtDumpMemoryLeaks();
    

    
    
    
    return 0;
}

