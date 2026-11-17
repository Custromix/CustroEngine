#define _CRTDBG_MAP_ALLOC
#include <cstdlib>
#include <crtdbg.h>
#include <windows.h>
#ifdef _DEBUG
#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)
#endif

#include <filesystem>

#include "CameraSystem.h"
#include "CustroEngine.h"
#include "Gameplay/Entity.h"
#include "Gameplay/Components/EntityComponents/SpatialComponents/CameraComponent.h"
#include "Input/Input.h"


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
    MeshComponent* MeshComp;
    BasicSystem* BasicSystemComp;
    
    float AngleSpeed = 20.0f;
    float Angle = 0.0f;
    
    float MovementSpeed = 2.0f;
    
    glm::vec3 Position = GetTransform()->GetWorldPosition();
    
    bool OtherMat = false;
    
    bool isRotating = false;
    
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
        if (OtherMat)
            MeshComp->SetMaterial(*Material::GetMaterialByName("TextureMaterial2"));
        else    
            MeshComp->SetMaterial(*Material::GetMaterialByName("TextureMaterial"));
        
        std::cout << "Le mesh est : " << MeshComp->GetMesh()->GetMeshName() << std::endl;
    }
    
    void Update(float deltaTime) override
    {
        if (!isRotating)
            return;
        
        Angle += AngleSpeed * deltaTime;
        GetTransform()->SetWorldRotation(glm::vec3(Angle, Angle*0.8, 0.0f));
    }
};

class Player : public Entity
{
    CameraComponent* Camera;
    
    glm::vec3 Position = GetTransform()->GetWorldPosition();
    glm::vec3 Rotation = GetTransform()->GetWorldRotation();
    
    float MovementSpeed = 15.0f;
    
    
    float Sensitivity = 150.f;
    
public:
    
    Player()
    {
        Camera = AddComponent<CameraComponent>();
        CameraSystem::Get().SetActiveCamera(Camera);
        //Input::EnableCursor(true);
    }
    
    void Start() override
    {
        GetTransform()->SetWorldPosition({-13.43,18.25,12.82});
        GetTransform()->SetWorldRotation({-10.99, 673.45, 0.0});
    }
    
    void Update(float deltaTime) override
    {
        Position = GetTransform()->GetWorldPosition();
        Rotation = GetTransform()->GetWorldRotation();
        glm::vec3 forward = GetTransform()->GetWorldForward();
        glm::vec3 right = GetTransform()->GetWorldRight();
        glm::vec3 up = GetTransform()->GetWorldUp();
        
        //std::cout << forward.x << " " << forward.y << " " << forward.z << std::endl;
        
        if (Input::IsKeyPressed(GLFW_KEY_ESCAPE))
            CustroEngine::Quit();
        
        if (Input::IsKeyPressed(GLFW_KEY_W))
            Position += forward * MovementSpeed * deltaTime;
        if (Input::IsKeyPressed(GLFW_KEY_S))
            Position -= forward * MovementSpeed * deltaTime;
        if (Input::IsKeyPressed(GLFW_KEY_A))
            Position -= right * MovementSpeed * deltaTime;
        if (Input::IsKeyPressed(GLFW_KEY_D))
            Position += right * MovementSpeed * deltaTime;
        if (Input::IsKeyPressed(GLFW_KEY_Q))
            Position -= up * MovementSpeed * deltaTime;
        if (Input::IsKeyPressed(GLFW_KEY_E))
            Position += up * MovementSpeed * deltaTime;
        
        float mouseX = Input::GetDeltaX();
        float mouseY = Input::GetDeltaY();
        
       
        //std::cout << "XPOS => " << Rotation.x << "YPOS => " << Rotation.y << "ZPOS => " << Rotation.z << std::endl;
        
        if (mouseX != 0.0f)
            Rotation += glm::vec3(0,1,0) * mouseX * Sensitivity * deltaTime;
        if (mouseY != 0.0f)
            Rotation += glm::vec3(1,0,0) * -mouseY * Sensitivity * deltaTime;
        
        if(Rotation.x > 89.0f)
            Rotation.x = 89.0f;
        if(Rotation.x < -89.0f)
            Rotation.x = -89.0f;
        
        GetTransform()->SetWorldRotation(Rotation);
        GetTransform()->SetWorldPosition(Position);
    }
    
};

int main() {
    
    float verticesData[] = {
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
    
    CustroEngine Engine = CustroEngine();
    
    std::optional<MeshData> Cube = MeshData();
    //MeshData&& Cube2 = MeshData();
    
    uint32 verticesCount = sizeof(verticesData) / (sizeof(float) * 3);
    for (uint32 i = 0; i < verticesCount; ++i)
    {
        Vertex v;
        v.position      = glm::vec3(verticesData[i * 3], verticesData[i * 3 + 1], verticesData[i * 3 + 2]);
        v.uv            = glm::vec2(uv[i * 2], uv[i * 2 + 1]);
        v.normal        = glm::vec3(0.0f, 0.0f, 0.0f); 
                
        /*if (normalSize > 0)
        {
            v.normal        = glm::vec3(normal[i * 3], normal[i * 3 + 1], normal[i * 3 + 2]);
            hasNormals = true;
        }*/
        
        Cube->Vertices.push_back(v);
    }

    Cube->Indices.assign(std::begin(indices), std::end(indices));
    Engine.ImportMesh(*Cube, "", "Cube");
    Cube.reset();
    
    Engine.ImportShader(GAME_PATH "/assets/Shaders/TextureShader.glsl", "TextureShader");
    Engine.ImportShader(GAME_PATH "/assets/Shaders/TextureShader.glsl", "TextureShader2");
    Texture* ContainerTexture = Engine.ImportTexture(GAME_PATH "/assets/container.jpg");
    Texture* AwasomeTexture = Engine.ImportTexture(GAME_PATH "/assets/awesomeface.png", "awesomeface");
    Texture* HerbeTexture = Engine.ImportTexture(GAME_PATH "/assets/herbe.jpg", "herbe");
    
    Material* MaterialAvecTexture = Engine.CreateMaterialFromShader("TextureShader", "TextureMaterial");
    Material* MaterialAvecTexture2 = Engine.CreateMaterialFromShader("TextureShader2", "TextureMaterial2");
    MaterialAvecTexture->SetTexture(HerbeTexture, "aTexture");
    MaterialAvecTexture2->SetTexture(ContainerTexture, "aTexture");
    
    Scene* MyScene = Engine.CreateScene();
    
    Engine.SetCurrentScene(MyScene);
    
    GameManager* MyGameManager = MyScene->Spawn<class GameManager>();
    
    Player* MyPlayer = MyScene->Spawn<class Player>(glm::vec3(0.0f, 0.0f, -3.0f));
    
    int floorSize[2] = {100, 100};
    
    for (int i = 0; i < floorSize[0]; ++i)
    {
        for (int j = 0; j < floorSize[1]; ++j)
        {
            ObjectQuelconque* Floor = MyScene->Spawn<class ObjectQuelconque>(glm::vec3(1.f * i, 1.f, -1.f * j));
            //if (i == 0 && j == 0)
            Floor->isRotating = true;
        }
    }
    
    
    
    // Code du jeu

    Engine.Lunch();
    
    
    return 0;
}

