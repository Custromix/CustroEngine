#include "Input.h"

#include <iostream>
#include <ostream>

#include "Window.h"



GLFWwindow* Input::Window;

float Input::LastX = 400.0f;
float Input::LastY = 300.0f;
float Input::DeltaX = 0.0f;
float Input::DeltaY = 0.0f;
bool Input::bIsCursorEnabled = false;


void Input::Init(GLFWwindow* window, float ScreenX, float ScreenY)
{
    Window = window;
    
    if (!bIsCursorEnabled)
        glfwSetInputMode(Window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    else
        glfwSetInputMode(Window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    
    LastX = ScreenX*0.5f;
    LastY = ScreenY*0.5f;
    
    glfwSetCursorPosCallback(Window, [](GLFWwindow* wind, double xpos, double ypos)
    {
        DeltaX = (float)xpos - LastX;
        DeltaY = (float)ypos - LastY;
        
        LastX = (float)xpos;
        LastY = (float)ypos;
        
        std::cout << "MouseX => " << DeltaX << " MouseY => " << DeltaY << std::endl;
     
    });
}

bool Input::IsKeyPressed(uint32 Key)
{
    return glfwGetKey(Window, Key) == GLFW_PRESS;
}

bool Input::IsKeyRealeased(uint32 Key)
{
    return glfwGetKey(Window, Key) == GLFW_RELEASE;
}

bool Input::IsKeyHolded(uint32 Key)
{
    return glfwGetKey(Window, Key) == GLFW_REPEAT;
}

void Input::ResetDeltas()
{
    DeltaX = 0;
    DeltaY = 0;
}

void Input::EnableCursor(bool bEnable)
{
    bIsCursorEnabled = bEnable;
    if (!bIsCursorEnabled)
        glfwSetInputMode(Window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    else
        glfwSetInputMode(Window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}
