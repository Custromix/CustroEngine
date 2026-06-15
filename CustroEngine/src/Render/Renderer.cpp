#include "Renderer.h"

#include "CameraSystem.h"
#include "CustroEngine.h"
#include "Gameplay/Entity.h"

Renderer::~Renderer()
{
    delete VertexShader;
    delete FragmentShader;
}

void Renderer::Init()
{
    glViewport(0, 0, CustroEngine::WINDOW_WIDTH, CustroEngine::WINDOW_HEIGHT);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glfwSwapInterval(0);
    glEnable(GL_DEPTH_TEST);
    
    VertexShader = new Shader("D:/Pro/Others/CustroEngine/CustroEngine/src/assets/Shader/vertexShader.glsl", "VertexShader", 0);
    FragmentShader = new Shader("D:/Pro/Others/CustroEngine/CustroEngine/src/assets/Shader/fragmentShader.glsl", "FragmentShader", 0);
    
    UpdateProjectionMatrix(CustroEngine::FOV, CustroEngine::WINDOW_WIDTH, CustroEngine::WINDOW_HEIGHT);
}

void Renderer::UnSubscribe(Shader* shader)
{
    Shaders.erase(std::remove(Shaders.begin(), Shaders.end(), shader), Shaders.end());
}

Shader* Renderer::CreateShader(const String ShaderPath, const String MeshName)
{
    int  success;
    char infoLog[512];
    
    uint32 ProgramId = glCreateProgram();
    
    Shader* MeshShader = new Shader(ShaderPath, MeshName, ProgramId);
    
    uint32 VertexShaderID = CreateShaderPass(GL_VERTEX_SHADER, VertexShader->GetShaderCode().CStr());
    uint32 FragmentShaderID = CreateShaderPass(GL_FRAGMENT_SHADER, FragmentShader->GetShaderCode().CStr(), MeshShader->GetShaderCode().CStr());
    
    
    glAttachShader(ProgramId, VertexShaderID);
    glAttachShader(ProgramId, FragmentShaderID);
    glLinkProgram(ProgramId);
    
    glGetProgramiv(ProgramId, GL_LINK_STATUS, &success);
    if(!success) {
        glGetProgramInfoLog(ProgramId, 512, nullptr, infoLog);
        std::cout << "ERROR::SHADER_PROGRAM::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    
    glDeleteShader(VertexShaderID);
    glDeleteShader(FragmentShaderID);
    
    glUseProgram(ProgramId);
    
    Shaders.push_back(MeshShader);
    
    return MeshShader;
}

void Renderer::InjectShaderCode(String shaderCode)
{
}

uint32 Renderer::CreateShaderPass(GLuint program, const char* PipelineShaderCode)
{
    int  success;
    char infoLog[512];
    
    uint32 ID = glCreateShader(program);
    glShaderSource(ID, 1, &PipelineShaderCode, nullptr); //Assign le shader GLSL au vertexShader
    glCompileShader(ID); //Compile le vertex shader
    
    glGetShaderiv(ID, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(ID, 512, nullptr, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    
    return ID;
}

uint32 Renderer::CreateShaderPass(GLuint program, const char* PipelineShaderCode, const char* CustomShaderCode)
{
    if (CustomShaderCode == nullptr || CustomShaderCode == "")
        std::cout << "ERROR::CUSTOM SHADER::NOT SET" << std::endl;

        
    std::string result = PipelineShaderCode;
    size_t pos = result.find("//USER");
    
    if (pos != std::string::npos)
        result.replace(pos, strlen("//USER"), CustomShaderCode);
    
    //std::cout << "Vrai SHADER : " << result << std::endl;
    
    const char* RealShaderCode = result.c_str();
    
    int  success;
    char infoLog[512];
    
    uint32 ID = glCreateShader(program);
    glShaderSource(ID, 1, &RealShaderCode, nullptr); //Assign le shader GLSL au vertexShader
    glCompileShader(ID); //Compile le vertex shader
    
    glGetShaderiv(ID, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(ID, 512, nullptr, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    
    return ID;
}

void Renderer::UpdateProjectionMatrix(uint32 FOV, uint32 width, uint32 height)
{
    projection = glm::perspectiveFov(glm::radians(static_cast<float>(FOV)), static_cast<float>(width), static_cast<float>(height), 0.1f, 100.0f);
}

void Renderer::UpdateViewMatrix()
{
}

void Renderer::Render()
{
    Transform CameraTransform = CameraSystem::Get().GetActiveCamera()->GetWorldTransform();
    
    view = glm::lookAt(CameraTransform.GetPosition(), CameraTransform.GetPosition() + CameraTransform.GetForward(), CameraSystem::Get().GetActiveCamera()->cameraUp);

    for (Shader* Shader : Shaders)
    {
        glUseProgram(Shader->GetProgramID());

        for (MeshComponent* MeshComp : Shader->GetMeshComponents())
        {
            for (uint32 iTexture = 0; iTexture < MeshComp->GetMaterial().GetTextures().size(); ++iTexture)
            {
                glActiveTexture(GL_TEXTURE0 + iTexture);
                glBindTexture(GL_TEXTURE_2D, MeshComp->GetMaterial().GetTextures()[iTexture]->GetID());
            }
            
            Shader->setMatrix4("model", MeshComp->GetWorldTransform().GetModel());
            Shader->setMatrix4("view", view);
            Shader->setMatrix4("projection", projection);
        
            MeshComp->GetMesh()->Draw();
        }
        
    }
    
/*
    for (int iMesh = 0; iMesh < MeshComponents.size(); ++iMesh)
    {
        if (!MeshComponents[iMesh])
            return;
        
        glUseProgram(MeshComponents[iMesh]->GetMaterial().GetShader().ProgramID);

        for (uint32 iTexture = 0; iTexture < MeshComponents[iMesh]->GetMaterial().GetShader().GetTextures().size(); ++iTexture)
        {
            glActiveTexture(GL_TEXTURE0 + iTexture);
            glBindTexture(GL_TEXTURE_2D, MeshComponents[iMesh]->GetMaterial().GetShader().GetTextures()[iTexture]->GetID());
        }
        
        MeshComponents[iMesh]->GetMaterial().GetShader().setMatrix4("model", MeshComponents[iMesh]->GetWorldTransform().GetModel());
        MeshComponents[iMesh]->GetMaterial().GetShader().setMatrix4("view", view);
        MeshComponents[iMesh]->GetMaterial().GetShader().setMatrix4("projection", projection);
        
        MeshComponents[iMesh]->GetMesh()->Draw();
    }
    */
}
