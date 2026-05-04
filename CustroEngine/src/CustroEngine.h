#pragma once
#include <GLFW/glfw3.h>
#include <iostream>

class CustroEngine
{

public:
    
    CustroEngine();
    
    void Init();
    
    void Start();
    
private:
    GLFWwindow* window = nullptr;
    
    
    
private: //Config File

    const unsigned int WINDOW_WIDTH = 800;
    const unsigned int WINDOW_HEIGHT = 600;
    
    
};