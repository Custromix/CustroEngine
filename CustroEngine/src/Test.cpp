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



class BasicSystem : public Component
{
    
public:
    BasicSystem(){}
    ~BasicSystem() override {}
    
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
    }
    
    void Start() override
    {
        MeshComp->SetMesh(Mesh::GetMeshByName("Triangle"));
        //std::cout << "Le mesh est : " << MeshComp->GetMesh()->GetMeshName() << std::endl;
        /*
        if (MeshComp->GetMesh()->GetMeshName())
            std::cout << "MESH TROUVE" << std::endl;
        else
        {
            std::cout << "MESH NOT TROUVE" << std::endl;
        }*/
    }
    
    void Update(float deltaTime) override
    {
        //std::cout << "DeltaTime = " + std::to_string(deltaTime)  << std::endl;
    }

};

int main() {
    

    float vertices[] = {
        0.5f,  0.5f, 0.0f,  // top right
        0.5f, -0.5f, 0.0f,  // bottom right
       -0.5f, -0.5f, 0.0f,  // bottom left
       -0.5f,  0.5f, 0.0f   // top left 
    };
    
    uint32 indices[] = {  // note that we start from 0!
        0, 1, 3,   // first triangle
        1, 2, 3    // second triangle
    };  
    
    
    
    //_CrtSetBreakAlloc(658); // le numéro de la fuite
    
    
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    
    CustroEngine* Engine = new CustroEngine();
    //Engine->Init();
    
    Engine->ImportMesh(vertices, sizeof(vertices), indices, sizeof(indices), "Triangle");
    
    Scene* MyScene = Engine->CreateScene();
    
    Engine->SetCurrentScene(MyScene);
    
    //GameManager* MyGameManager = MyScene->Spawn<class GameManager>();
    
    ObjectQuelconque* Cube = MyScene->Spawn<class ObjectQuelconque>(glm::vec3(9.f, 0.0f, 0.0f));
    
    
    // Code du jeu

    Engine->Lunch();
    
    delete Engine;
    
    
    _CrtDumpMemoryLeaks();
    

    
    
    return 0;
}

