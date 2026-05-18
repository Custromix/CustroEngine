#include "Renderer.h"

#include "CustroEngine.h"

void Renderer::Init()
{
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
    
    std::cout << "Vrai SHADER : " << result << std::endl;
    
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

void Renderer::Draw()
{
    for (int i = 0; i < MeshComponents.size(); ++i)
    {
        if (!MeshComponents[i])
            return;
        
        //TODO: Compile le shader bien avant le draw.
        
        int  success;
        char infoLog[512];
    
        uint32 VertexShaderID = CreateShaderPass(GL_VERTEX_SHADER, VertexShader->ShaderCode.CStr());
        
        if (!MeshComponents[i]->GetShader())
        {
            std::cout << "ERROR::CUSTOM SHADER::NOT SET " << infoLog << std::endl;

            return;
        }
            
        uint32 FragmentShaderID = CreateShaderPass(GL_FRAGMENT_SHADER, FragmentShader->ShaderCode.CStr(), MeshComponents[i]->GetShader()->ShaderCode.CStr());
     
    
        ProgramId = glCreateProgram();
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
        
        Shader::setMatrix4(ProgramId, "model", MeshComponents[i]->Owner()->GetTransform()->GetModel());
        Shader::setMatrix4(ProgramId, "view", view);
        Shader::setMatrix4(ProgramId, "projection", projection);
        MeshComponents[i]->GetMesh()->Render();
    }
    
    glDeleteProgram(ProgramId);
}

