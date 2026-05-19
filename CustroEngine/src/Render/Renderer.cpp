#include "Renderer.h"

#include "CustroEngine.h"

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
    
    VertexShader = new Shader("D:/Pro/Others/CustroEngine/CustroEngine/src/assets/Shader/vertexShader.glsl", "VertexShader");
    FragmentShader = new Shader("D:/Pro/Others/CustroEngine/CustroEngine/src/assets/Shader/fragmentShader.glsl", "FragmentShader");
    
    view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f)); 
    projection = glm::perspectiveFov(glm::radians(50.0f), static_cast<float>(CustroEngine::WINDOW_WIDTH), static_cast<float>(CustroEngine::WINDOW_HEIGHT), 0.1f, 100.0f);
}

void Renderer::Subscribe(MeshComponent* component)
{
    MeshComponents.push_back(component);
}

void Renderer::UnSubscribe(MeshComponent* component)
{
    MeshComponents.erase(std::remove(MeshComponents.begin(), MeshComponents.end(), component), MeshComponents.end());
}

Shader* Renderer::CreateShader(const String ShaderPath, const String MeshName)
{
    int  success;
    char infoLog[512];
    
    Shader* MeshShader = new Shader(ShaderPath, MeshName);
    
    uint32 VertexShaderID = CreateShaderPass(GL_VERTEX_SHADER, VertexShader->ShaderCode.CStr());
    uint32 FragmentShaderID = CreateShaderPass(GL_FRAGMENT_SHADER, FragmentShader->ShaderCode.CStr(), MeshShader->ShaderCode.CStr());
    
    uint32 ProgramId = glCreateProgram();
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
    
    MeshShader->ProgramID = ProgramId;
    
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

void Renderer::Render()
{
    for (int iMesh = 0; iMesh < MeshComponents.size(); ++iMesh)
    {
        if (!MeshComponents[iMesh])
            return;
        
        glUseProgram(MeshComponents[iMesh]->GetShader().ProgramID);

        for (uint32 iTexture = 0; iTexture < MeshComponents[iMesh]->GetShader().GetTextures().size(); ++iTexture)
        {
            glActiveTexture(GL_TEXTURE0 + iTexture);
            glBindTexture(GL_TEXTURE_2D, MeshComponents[iMesh]->GetShader().GetTextures()[iTexture]->GetID());
        }
        
        MeshComponents[iMesh]->GetShader().setMatrix4("model", MeshComponents[iMesh]->Owner()->GetTransform()->GetModel());
        MeshComponents[iMesh]->GetShader().setMatrix4("view", view);
        MeshComponents[iMesh]->GetShader().setMatrix4("projection", projection);
        
        MeshComponents[iMesh]->GetMesh()->Draw();
        
        glDeleteProgram(MeshComponents[iMesh]->GetShader().ProgramID);
    }
}

