#define _CRTDBG_MAP_ALLOC
#include <cstdlib>
#include <crtdbg.h>
#ifdef _DEBUG
#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)
#endif

#include "CustroEngine.h"
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
public:
    Texture* aTexture;
    
    MeshComponent* MeshComp;
    BasicSystem* BasicSystemComp;
    
    float AngleSpeed = 45.0f;
    float Angle = 0.0f;
    
public:
    ObjectQuelconque()
    {
        MeshComp = AddComponent<MeshComponent>();
        BasicSystemComp = AddComponent<class BasicSystem>();
    }
    
    ~ObjectQuelconque() override
    {
    }
    
    void Start() override
    {
        MeshComp->SetMesh(Mesh::GetMeshByName("Cube"));
        MeshComp->SetShader(*Shader::GetShaderByName("DefaultShader"));
        MeshComp->GetShader().SetTexture(aTexture, "aTexture");
        
        std::cout << "Le mesh est : " << MeshComp->GetMesh()->GetMeshName() << std::endl;
    }
    
    void Update(float deltaTime) override
    {
        Angle += AngleSpeed * deltaTime;
        GetTransform()->SetRotation(glm::vec3(Angle, Angle*0.8, 0.0f));
    }

};

int main() {
    
    float vertices[] = {
        // Front
        -0.5f,  0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,
         0.5f, -0.5f,  0.5f,
        -0.5f, -0.5f,  0.5f,
        // Back
         0.5f,  0.5f, -0.5f,
        -0.5f,  0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
        // Right
         0.5f,  0.5f,  0.5f,
         0.5f,  0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f, -0.5f,  0.5f,
        // Left
        -0.5f,  0.5f, -0.5f,
        -0.5f,  0.5f,  0.5f,
        -0.5f, -0.5f,  0.5f,
        -0.5f, -0.5f, -0.5f,
        // Top
        -0.5f,  0.5f, -0.5f,
         0.5f,  0.5f, -0.5f,
         0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,
        // Bottom
        -0.5f, -0.5f,  0.5f,
         0.5f, -0.5f,  0.5f,
         0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,
    };

    float uv[] = {
        // Front
        0.0f, 1.0f,  1.0f, 1.0f,  1.0f, 0.0f,  0.0f, 0.0f,
        // Back
        0.0f, 1.0f,  1.0f, 1.0f,  1.0f, 0.0f,  0.0f, 0.0f,
        // Right
        0.0f, 1.0f,  1.0f, 1.0f,  1.0f, 0.0f,  0.0f, 0.0f,
        // Left
        0.0f, 1.0f,  1.0f, 1.0f,  1.0f, 0.0f,  0.0f, 0.0f,
        // Top
        0.0f, 1.0f,  1.0f, 1.0f,  1.0f, 0.0f,  0.0f, 0.0f,
        // Bottom
        0.0f, 1.0f,  1.0f, 1.0f,  1.0f, 0.0f,  0.0f, 0.0f,
    };

    uint32 indices[] = {
        0,  1,  2,  2,  3,  0,  // Front
        4,  5,  6,  6,  7,  4,  // Back
        8,  9,  10, 10, 11, 8,  // Right
        12, 13, 14, 14, 15, 12, // Left
        16, 17, 18, 18, 19, 16, // Top
        20, 21, 22, 22, 23, 20, // Bottom
    };
    
    
    //_CrtSetBreakAlloc(658); // le numéro de la fuite
    
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    
    CustroEngine* Engine = new CustroEngine();
    
    Engine->ImportMesh(vertices, sizeof(vertices), uv, sizeof(uv), nullptr, 0, indices, sizeof(indices), "Cube");
    Engine->ImportShader("D:/Pro/Others/CustroEngine/CustroEngine/src/DefaultShader.glsl", "DefaultShader");
    Engine->ImportTexture("D:/Pro/Others/CustroEngine/CustroEngine/src/assets/container.jpg");
    Engine->ImportTexture("D:/Pro/Others/CustroEngine/CustroEngine/src/assets/AM.png", "awesomeface");
    
    Scene* MyScene = Engine->CreateScene();
    
    Engine->SetCurrentScene(MyScene);
    
    GameManager* MyGameManager = MyScene->Spawn<class GameManager>();
    
    ObjectQuelconque* Cube = MyScene->Spawn<class ObjectQuelconque>(glm::vec3(-0.8f, 0.0f, -0.5f));
    Cube->aTexture = Texture::GetTextureByName("container");
    
    ObjectQuelconque* Cube2 = MyScene->Spawn<class ObjectQuelconque>(glm::vec3(0.8f, 0.0f, -0.5f));
    Cube2->aTexture = Texture::GetTextureByName("awesomeface");
    
    
    // Code du jeu

    Engine->Lunch();
    
    delete Engine;
    
    
    return 0;
}

