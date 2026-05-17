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
    
    float AngleSpeed = 45.0f;
    float Angle = 0.0f;
    
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
        MeshComp->SetMesh(Mesh::GetMeshByName("Cube"));
        
        std::cout << "Le mesh est : " << MeshComp->GetMesh()->GetMeshName() << std::endl;
        
        /*if (MeshComp->GetMesh()->GetMeshName())
            std::cout << "MESH TROUVE" << std::endl;
        else
        {
            std::cout << "MESH NOT TROUVE" << std::endl;
        }*/
    }
    
    void Update(float deltaTime) override
    {
        Angle += AngleSpeed * deltaTime;
        GetTransform()->SetRotation(glm::vec3(Angle, Angle, 0.0f));
        std::cout << "Angle : " << Angle << std::endl;
    }

};

int main() {
    
    float vertices[] = {
        -0.5,  0.5,  0.5, // top left devant
         0.5,  0.5,  0.5, // top right devant
         0.5, -0.5,  0.5, // bottom right devant
        -0.5, -0.5,  0.5, // bottom left devant

        -0.5,  0.5,  -0.5, // top left  derrier
         0.5,  0.5,  -0.5, // top right derrier
         0.5, -0.5,  -0.5, // bottom right derrier
        -0.5, -0.5,  -0.5  // bottom left derrier
    };
    
    float uv[] = {
        1.0f, 1.0f,     // top right
        1.0f, 0.0f,     // bottom right
        0.0f, 0.0f,     // bottom left
        0.0f, 1.0f,     // top left 
        
        1.0f, 1.0f,     // top right
        1.0f, 0.0f,     // bottom right
        0.0f, 0.0f,     // bottom left
        0.0f, 1.0f,     // top left 
    };
    
    uint32 indices[] = {
        // Devant
        0, 1, 2,
        2, 3, 0,
        // Derrière
        4, 5, 6,
        6, 7, 4,
        // Droite
        1, 5, 6,
        6, 2, 1,
        // Gauche
        0, 4, 7,
        7, 3, 0,
        // Haut
        0, 1, 5,
        5, 4, 0,
        // Bas
        3, 2, 6,
        6, 7, 3,
    };
    
    
    
    //_CrtSetBreakAlloc(658); // le numéro de la fuite
    
    
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    
    CustroEngine* Engine = new CustroEngine();
    
    Engine->ImportMesh(vertices, sizeof(vertices), uv, sizeof(uv), nullptr, 0, indices, sizeof(indices), "Cube");
    
    Scene* MyScene = Engine->CreateScene();
    
    Engine->SetCurrentScene(MyScene);
    
    GameManager* MyGameManager = MyScene->Spawn<class GameManager>();
    
    ObjectQuelconque* Cube = MyScene->Spawn<class ObjectQuelconque>(glm::vec3(0.0f, 0.0f, 0.0f));
    
    
    
    // Code du jeu

    Engine->Lunch();
    
    delete Engine;
    
    
    _CrtDumpMemoryLeaks();
    
    
    return 0;
}

