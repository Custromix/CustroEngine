#pragma once
#include <GLFW/glfw3.h>

#include "types.hpp"

using namespace Engine;

class Input
{
public:
    static void Init(GLFWwindow* window, float ScreenX, float ScreenY);
    
    static bool IsKeyPressed(uint32 Key);
    static bool IsKeyRealeased(uint32 Key);
    static bool IsKeyHolded(uint32 Key);
    
    static float GetPosX();
    static float GetPosY();
    
    static float GetDeltaX() { return DeltaX; }
    static float GetDeltaY() { return DeltaY; }
    
    static void ResetDeltas();
    
    static void EnableCursor(bool bEnable);
    
private:
    
    static GLFWwindow* Window;
    
    static float LastX, LastY;
    static float DeltaX, DeltaY;
    
    static bool bIsCursorEnabled;
};