#include "Shader.h"
#include <GLFW/glfw3.h>
#include <iostream>
#define STB_IMAGE_IMPLEMENTATION
#include <algorithm>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "utils/stb_image.h"

#include <cstdlib>  // rand, srand

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void get_key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow* window);
float NormalizeRGB(float colorChan);

const unsigned int WINDOW_WIDTH = 1000;
const unsigned int WINDOW_HEIGHT = 800;

float FOV = 45.0f;

bool isWireframeRenderMode = false;

float AlphaBlend = 0.2f;

float MovementSpeed = 10.0f;

float ElapsedTime = 0.0f;

float lastX = WINDOW_WIDTH/2; 
float lastY = WINDOW_HEIGHT/2;

glm::vec3 cameraPosition;

bool firstMouse = true;

float pitch  =    0.0f;
float yaw    =   -90.0f;
float roll   =    0.0f;

glm::vec3 cameraForward;
glm::vec3 cameraBackward;
glm::vec3 cameraRight;
glm::vec3 cameraUp;

int main() {
    /**
     * Init GLFW et set la version d'opengl a utilisé et le profile d'opengl
     */
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    // Crée la window et set la taille de la window
    GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Kader's Engine", nullptr, nullptr);
    if (window == nullptr)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    
    glfwMakeContextCurrent(window); //Set la window comme context a utilisé dans le main thread pour opengl 
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback); // Set la callback a chaque fois que la taille de la fenetre est rezise
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);  
    glfwSetKeyCallback(window, get_key_callback);
    glfwSetCursorPosCallback(window, mouse_callback);  
    glfwSetScrollCallback(window, scroll_callback); 
    
    /**
     * Init et vérifie si GLAD est bien init
     * Doit être appelé après MakeContextCurrent
     */
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) 
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    
    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT); //Set la taille de la window mais pour opengl, si la taille est différente de la window le rendu sera étiré ou retrecie
    
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glEnable(GL_DEPTH_TEST);
    
    srand(122465);
    
    /* Mesh */
    float vertices2[] = {
        // positions          // colors           // texture coords
        0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
        0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
       -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
       -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left 
        
        
   }; 
    
    unsigned int indices[] = {
        0, 1, 2,
        2, 3, 0,
    };
    
    float vertices[] = {
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };
    
    glm::vec3 cubePositions[] = {
        glm::vec3( 0.0f,  0.0f,  0.0f), 
        glm::vec3( 2.0f,  5.0f, -15.0f), 
        glm::vec3(-1.5f, -2.2f, -2.5f),  
        glm::vec3(-3.8f, -2.0f, -12.3f),  
        glm::vec3( 2.4f, -0.4f, -3.5f),  
        glm::vec3(-1.7f,  3.0f, -7.5f),  
        glm::vec3( 1.3f, -2.0f, -2.5f),  
        glm::vec3( 1.5f,  2.0f, -2.5f), 
        glm::vec3( 1.5f,  0.2f, -1.5f), 
        glm::vec3(-1.3f,  1.0f, -1.5f)  
    };
    
    /***
     * Création du VAO pour le VBO triangle
     */
    
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    
    unsigned int EBO;
    glGenBuffers(1, &EBO); // Crée un buffer vide
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO); // Set le current buffer GL_ELEMENT_ARRAY_BUFFER à l'id EBO
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW); // Rempli le buffer avec les faces triangulaire du mesh en static draw donc pas modifiable
    
    unsigned int VBO;
    glGenBuffers(1, &VBO); // Crée un buffer vide
    glBindBuffer(GL_ARRAY_BUFFER, VBO); // Set le current buffer GL_ARRAY_BUFFER à l'id VBO
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); // Rempli le buffer avec les vertices du mesh en static draw donc pas modifiable
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0); // Dire a opengl comment lire le buffer des vertices
    glEnableVertexAttribArray(0); // Active le vertex attribut au slot 0;
    
    // glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3*sizeof(float))); // Dire a opengl comment lire le buffer des couleurs des vertices
    // glEnableVertexAttribArray(1); // Active le vertex attribut au slot 1;
    
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3*sizeof(float))); // Dire a opengl comment lire le buffer des textCoords
    glEnableVertexAttribArray(2); // Active le vertex attribut au slot 2;
    
    // glBindVertexArray(0); // Unbind le VAO
    // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); // Unbind le GL_ELEMENT_ARRAY_BUFFER
    // glBindBuffer(GL_ARRAY_BUFFER, 0); // Unbind le buffer GL_ARRAY_BUFFER
    
    Shader ourShader(
        "../CustroEngine/src/Shader/vertexShader.glsl",
        "../CustroEngine/src/Shader/fragmentShader.glsl"
    );
    
    /* flip texture */
    stbi_set_flip_vertically_on_load(true); 
    
    /* Settings of wrapping et filtering texture option */
    unsigned int texture;
    glGenTextures(1, &texture);
    
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    
    int width, height, nrChannels;
    unsigned char *data = nullptr;
    
    data = stbi_load("../CustroEngine/src/assets/container.jpg", &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);
    data = nullptr;
    
    
    unsigned int texture2;
    glGenTextures(1, &texture2);
    
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, texture2);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    
    
    data = stbi_load("../CustroEngine/src/assets/awesomeface.png", &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);
    data = nullptr;
    
    /* CAMERA */
    glm::vec3 right    =   glm::vec3(1.0f, 0.0f, 0.0f);
    glm::vec3 up       =   glm::vec3(0.0f, 1.0f, 0.0f);
    glm::vec3 forward  =   glm::vec3(0.0f, 0.0f, 1.0f);
    
    glm::vec3 direction;
    direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    direction.y = sin(glm::radians(pitch));
    direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    
    cameraForward = glm::normalize(direction);
    

    cameraPosition = glm::vec3(0.0f, 0.0f, 3.0f);
    
    float angle = 0.0f;
    float speedAngle = glm::pi<float>() * 0.5f;
    
    double lastTime  = glfwGetTime();
    
    unsigned int modelLoc = glGetUniformLocation(ourShader.ID, "model");
    unsigned int viewLoc = glGetUniformLocation(ourShader.ID, "view");
    unsigned int projectionLoc = glGetUniformLocation(ourShader.ID, "projection");
    
    float angleCubeRot [] = { 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f};
    float speedRand [] = { rand() % 100/100.f, rand() % 100/100.f, rand() % 100/100.f, rand() % 100/100.f, rand() % 100/100.f, rand() % 100/100.f, rand() % 100/100.f, rand() % 100/100.f, rand() % 100/100.f, rand() % 100/100.f};
    
    
    while (!glfwWindowShouldClose(window))
    {
        ElapsedTime = (float)(glfwGetTime() - lastTime);
        lastTime = glfwGetTime();
        //InputManagement
        processInput(window);
        
        //Processing
        float timeValue = glfwGetTime();
        float greenValue = sin(timeValue) / 2.0f + 0.5f;
        
        angle += speedAngle * ElapsedTime;
    
        cameraRight = glm::normalize(glm::cross(cameraForward, up));
        cameraUp = glm::normalize(glm::cross(cameraRight, cameraForward));
        
        
        
        glm::mat4 model = glm::mat4(1.0f);
        
        glm::mat4 view = glm::mat4(1.0f);
        
        view = glm::lookAt(cameraPosition, cameraPosition + cameraForward, cameraUp);
        
        // glm::mat4 R = glm::mat4(
        //     glm::vec4(cameraRight, 0.0f),
        //     glm::vec4(cameraUp, 0.0f),
        //     glm::vec4(-cameraForward, 0.0f),
        //     glm::vec4(0.0f, 0.0f, 0.0f, 1.0f)
        //     );
        // glm::mat4 T = glm::mat4(
        //     glm::vec4(1.0f, 0.0f, 0.0f, 0.0f),
        //     glm::vec4(0.0f, 1.0f, 0.0f, 0.0f),
        //     glm::vec4(0.0f, 0.0f, 1.0f, 0.0f),
        //     glm::vec4(-cameraPosition, 1.0f)
        //     );
        //
        // view = R * T;
        
        
        
        glm::mat4 projection;
        projection = glm::perspective(glm::radians(FOV), (float)WINDOW_WIDTH/(float)WINDOW_HEIGHT, 0.1f, 100.0f);
        //projection = glm::perspectiveFov(glm::radians(90.0f), (float)WINDOW_WIDTH, (float)WINDOW_HEIGHT, 1.0f, 100.0f);

        
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, &model[0][0]);
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &view[0][0]);
        glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, &projection[0][0]);
        
        
        //Rendering
        
        glClearColor(NormalizeRGB(78),NormalizeRGB(159),NormalizeRGB(229), 1.f); //Set la prochaine valeur de couleur pour le buffer GL_COLOR_BUFFER_BIT
        //glClearColor(NormalizeRGB(15),NormalizeRGB(15),NormalizeRGB(15), 1.f); //Set la prochaine valeur de couleur pour le buffer GL_COLOR_BUFFER_BIT
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //Clear le buffer GL_COLOR_BUFFER_BIT avec la valeur de couleur précédément séléctionné et le GL_DEPTH_BUFFER_BIT pour rendre de nouveau les pixels a l'écran
        
        ourShader.use();
        
        glBindVertexArray(VAO);
        
        ourShader.setInt("Texture1", 0);
        ourShader.setInt("Texture2", 1);
        ourShader.setFloat("AlphaBlend", AlphaBlend);
        
        
        
        for (unsigned int i = 0; i < sizeof(cubePositions)/sizeof(cubePositions[0]); ++i)
        {
            glm::mat4 transform = glm::mat4(1.0f);
            
            
            float randAngleSpeed = speedRand[i] * (2.0f * glm::pi<float>());
            
            angleCubeRot[i] += randAngleSpeed * ElapsedTime;
            
            glm::mat4 scale = glm::scale(transform, glm::vec3(1.0f, 1.0f, 1.0f));
            glm::mat4 rotation = glm::rotate(transform, angleCubeRot[i], glm::vec3(1.0f, 1.0f, 0.0f));
            glm::mat4 translate = glm::translate(transform, cubePositions[i]);
            
            transform = translate * rotation * scale;
            unsigned int transformLoc = glGetUniformLocation(ourShader.ID, "transform");
            glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));
            
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }
        
        glBindVertexArray(0);
        
        // check and call events and swap the buffers
        glfwSwapBuffers(window);
        glfwPollEvents(); 
    }
    
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    
    glfwTerminate();
    return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
        cameraPosition += MovementSpeed * ElapsedTime * cameraForward;
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
        cameraPosition -= MovementSpeed * ElapsedTime * cameraForward;
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    {
        cameraPosition -= MovementSpeed * ElapsedTime * cameraRight;
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {
        cameraPosition += MovementSpeed * ElapsedTime * cameraRight;
    }
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
    {
        cameraPosition += MovementSpeed * ElapsedTime * cameraUp;
    }
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
    {
        cameraPosition -= MovementSpeed * ElapsedTime * cameraUp;
    }
    
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
        AlphaBlend = std::clamp(AlphaBlend + 1.0f * ElapsedTime, 0.0f, 1.0f);
    else if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
        AlphaBlend = std::clamp(AlphaBlend - 1.0f * ElapsedTime, 0.0f, 1.0f);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    FOV -= (float)yoffset;
    if (FOV < 1.0f)
        FOV = 1.0f;
    if (FOV > 50.0f)
        FOV = 50.0f; 
}

void get_key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_F1 && action == GLFW_PRESS)
    {
        if (isWireframeRenderMode)
        {
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            isWireframeRenderMode = false;
        }
        else
        {
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            isWireframeRenderMode = true;
        }
    }
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }
    
    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates range from bottom to top
    lastX = xpos;
    lastY = ypos;

    const float sensitivity = 0.1f;
    xoffset *= sensitivity;
    yoffset *= sensitivity;
    
    yaw   += xoffset;
    pitch += yoffset;  
    
    if(pitch > 89.0f)
        pitch =  89.0f;
    if(pitch < -89.0f)
        pitch = -89.0f;
    
    glm::vec3 direction;
    direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    direction.y = sin(glm::radians(pitch));
    direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    
    cameraForward = glm::normalize(direction);
}

float NormalizeRGB(float colorChan)
{
    return colorChan/255.f;
}
