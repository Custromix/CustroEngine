#include "CustroEngine.h"

#include "Render/Renderer.h"
#include "utils/Utils.h"

#define STB_IMAGE_IMPLEMENTATION
#include "CameraSystem.h"
#include "Input/Input.h"
#include "Render/Texture.h"
#include "utils/stb_image.h"

CustroEngine* CustroEngine::Instance;

CustroEngine::CustroEngine()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Custro Engine", nullptr, nullptr);
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
    
    Input::Init(window, WINDOW_WIDTH, WINDOW_HEIGHT);
    
    Renderer::Get().Init();

    glfwSetFramebufferSizeCallback(window, [](GLFWwindow* window, int width, int height){
        glViewport(0, 0, width, height);
        Renderer::Get().UpdateProjectionMatrix(FOV, WINDOW_WIDTH, WINDOW_HEIGHT);
    });
    
    std::cout << "\033[33m" << "CustroEngine::INITIALIZED" << "\033[0m" << std::endl;
    
    Instance = this;
}

CustroEngine::~CustroEngine()
{
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
    
    for (int i = 0; i < GarbagedShaders.size(); ++i)
    {
        delete GarbagedShaders[i];
        GarbagedShaders[i] = nullptr;
    }
    
    currentScene = nullptr;
    
    glfwDestroyWindow(window);
    glfwTerminate();
    
    GameObject::CustroEngineInstance = nullptr;
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
Mesh* CustroEngine::ImportMesh(float vertices[], size_t verticesSize, float uv[], size_t uvSize, float normals[], size_t normalsSize, uint32 indices[], size_t indicesSize, const String MeshName)
{
    GarbagedMeshes.push_back(new Mesh(vertices, verticesSize, uv, uvSize, normals, normalsSize, indices, indicesSize, MeshName));
    return GarbagedMeshes.back();
}

Shader* CustroEngine::ImportShader(const String ShaderPath, const String MeshName)
{
    GarbagedShaders.push_back(Renderer::Get().CreateShader(ShaderPath, MeshName));
    return GarbagedShaders.back();
}

Texture* CustroEngine::ImportTexture(const String TexturePath, String TextureName)
{
    if (TextureName.IsEmpty())
    {
        std::string stdStringPath = TexturePath.CStr();
        std::string filename = stdStringPath.substr(stdStringPath.find_last_of("/\\") + 1);
        filename = filename.substr(0, filename.find_last_of("."));
    
        TextureName = filename.c_str();
    }
    
    GarbagedTexture.push_back(new Texture(TexturePath, TextureName));
    return GarbagedTexture.back();
}

Scene* CustroEngine::CreateScene()
{
    GarbagedScene.push_back(new Scene());
    return GarbagedScene.back();
}

void CustroEngine::Quit()
{
    glfwSetWindowShouldClose(Instance->window, true);
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
        CountFPS++;
        
        if (seconds >= 1.0f)
        {
            FPS = CountFPS;
            CountFPS = 0;
            seconds = 0.f;
            std::cout << " FPS : " + std::to_string(FPS) << std::endl;
            _CrtMemState memState;
            _CrtMemCheckpoint(&memState);
            std::cout << "Heap used: " << memState.lSizes[_NORMAL_BLOCK] << " bytes" << std::endl;
        }
        
        for (int i = 0; i < currentScene->GetGameObjects().size(); ++i)
        {
            currentScene->GetGameObjects()[i]->Update(deltaTime);
        }
        
        Input::ResetDeltas();
        
        /***  RENDER  ***/
        
        glClearColor(Utils::NormalizeRGB(78.f), Utils::NormalizeRGB(159.f), Utils::NormalizeRGB(229.f), 1.f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        Renderer::Get().Render();
        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    
    glfwDestroyWindow(window);
    glfwTerminate();
}

