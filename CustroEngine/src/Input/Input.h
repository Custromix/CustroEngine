#pragma once
#include <GLFW/glfw3.h>

#include "types.hpp"

using namespace Engine;

class Input
{
public:
    static bool IsKeyPressed(uint32 Key);
    static bool IsKeyRealeased(uint32 Key);
    static bool IsKeyHolded(uint32 Key);
    
    static void SetContext(GLFWwindow* Context) { Window = Context; } 
    
private:
    
    static GLFWwindow* Window;
    
};
