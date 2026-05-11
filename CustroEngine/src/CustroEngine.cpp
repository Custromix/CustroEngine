#include "CustroEngine.h"

#include "utils/Utils.h"


CustroEngine::CustroEngine()
{
    //GameObject::SetEngine(this);
}

CustroEngine::~CustroEngine()
{
    delete shader;
    delete currentScene;
    
    glfwDestroyWindow(window);
    glfwTerminate();
    
    GameObject::CustroEngineInstance = nullptr;
}

void CustroEngine::Init()
{
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
    
    std::cout << "CACA PROUT" << std::endl;
    
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
    } 
    
    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    
    //glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED); //Désactive le cursor
    
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glEnable(GL_DEPTH_TEST);
    
    shader = new Shader("D:/Pro/Others/CustroEngine/CustroEngine/src/Shader/vertexShader.glsl", "D:/Pro/Others/CustroEngine/CustroEngine/src/Shader/fragmentShader.glsl");
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

Mesh* CustroEngine::ImportMesh(char path, const char* MeshName)
{

    float vertices[] = {
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.0f,  0.5f, 0.0f
    };
    
    Meshes.push_back(Mesh(vertices, MeshName));
    return &Meshes.back();
}

//TODO: Supprimer cette fonction quand on aura fait le parser
Mesh* CustroEngine::ImportMesh(float vertices[], const char* MeshName)
{
    std::cout << "CustroEngine::ImportMesh 2" << std::endl;

    Meshes.push_back(Mesh(vertices, MeshName));
    std::cout << "CustroEngine::ImportMesh" << std::endl;
    return &Meshes.back();
}

Mesh* CustroEngine::GetMesh(const char* MeshName)
{
    //Mesh::GetMesh();
    return nullptr;
}

void CustroEngine::PreStart()
{
    
}

void CustroEngine::Start()
{
    for (int i = 0; i < currentScene->GetGameObjects().size(); ++i)
    {
        currentScene->GetGameObjects()[i]->Start();
    }
}

void CustroEngine::Update()
{
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
        glBindVertexArray(0);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        
        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    
    glfwDestroyWindow(window);
    glfwTerminate();
}

