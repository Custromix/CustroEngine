#include "CustroEngine.h"

#include "Render/Renderer.h"
#include "utils/Utils.h"


CustroEngine::CustroEngine()
{
    //GameObject::SetEngine(this);
    
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Kader's Engine", nullptr, nullptr);
    if (window == nullptr)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
    }
    
    glfwMakeContextCurrent(window);
    
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
    } 
    
    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    
    //glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED); //Désactive le cursor
    
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    //glEnable(GL_DEPTH_TEST);
    
    shader = new Shader("D:/Pro/Others/CustroEngine/CustroEngine/src/Shader/vertexShader.glsl", "D:/Pro/Others/CustroEngine/CustroEngine/src/Shader/fragmentShader.glsl");
}

CustroEngine::~CustroEngine()
{
    delete shader;
    
    for (int i = 0; i < GarbagedScene.size(); ++i)
    {
        delete GarbagedScene[i];
        GarbagedScene[i] = nullptr;
    }
    
    
    for (int i = 0; i < GarbagedMeshes.size(); ++i)
    {
        delete GarbagedMeshes[i];
        GarbagedMeshes[i] = nullptr;
    }
    
    
    currentScene = nullptr;
    
    glfwDestroyWindow(window);
    glfwTerminate();
    
    GameObject::CustroEngineInstance = nullptr;
}

void CustroEngine::Init()
{
    
}

void CustroEngine::Lunch()
{
    PreStart();
    Start();
    Update();
}

void CustroEngine::SetCurrentScene(Scene* Scene)
{
    currentScene = Scene;
}

/*Mesh* CustroEngine::ImportMesh(char path, const char* MeshName)
{

    
    GarbagedMeshes.push_back(new Mesh(vertices, MeshName));
    return GarbagedMeshes.back();
}*/

//TODO: Supprimer cette fonction quand on aura fait le parser
Mesh* CustroEngine::ImportMesh(float vertices[], size_t verticesSize, uint32 indices[], size_t indicesSize, const char* MeshName)
{
    GarbagedMeshes.push_back(new Mesh(vertices, verticesSize, indices, indicesSize, MeshName));
    return GarbagedMeshes.back();
}

Mesh* CustroEngine::GetMesh(const String MeshName)
{
    //Mesh::GetMesh();
    return nullptr;
}

Scene* CustroEngine::CreateScene()
{
    GarbagedScene.push_back(new Scene());
    return GarbagedScene.back();
}

void CustroEngine::PreStart()
{
    
}

void CustroEngine::Start()
{
    if (!currentScene)
        return;
    
    for (int i = 0; i < currentScene->GetGameObjects().size(); ++i)
    {
        currentScene->GetGameObjects()[i]->StartEngineClass();
    }
}

void CustroEngine::Update()
{
    if (!currentScene)
        return;
    
    if (!window)
        return;
    
    float lastTime = glfwGetTime();
    float seconds = 0.f;
    int CountFPS = 0;
    int FPS = 0;
    
    while (!glfwWindowShouldClose(window))
    {
        /***  LOGIQUE  ***/
        
        float currentTime = glfwGetTime();
        float deltaTime = currentTime - lastTime;
        lastTime = currentTime;
        
        seconds += deltaTime;
        
        if (seconds >= 1.0f)
        {
            CountFPS++;
            seconds = 0.f;
            FPS = CountFPS;
            CountFPS = 0;
        }
        else
            CountFPS++;
        
        //std::cout << " FPS : " + std::to_string(FPS) << std::endl;
        
        for (int i = 0; i < currentScene->GetGameObjects().size(); ++i)
        {
            currentScene->GetGameObjects()[i]->Update(deltaTime);
        }
        
        /***  RENDER  ***/
        
        glClearColor(Utils::NormalizeRGB(78.f), Utils::NormalizeRGB(159.f), Utils::NormalizeRGB(229.f), 1.f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        
        shader->use();
        
        Renderer::Draw();
        
        /*for (int i = 0; i < currentScene->GetMeshComponents().size(); ++i)
        {
            currentScene->GetMeshComponents()[i]->GetMesh()->Render();
        }*/
        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    
    glfwDestroyWindow(window);
    glfwTerminate();
}

