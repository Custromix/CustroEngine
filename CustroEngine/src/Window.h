#pragma once
#include "types.hpp"
#include <GLFW/glfw3.h>

using namespace CustroEngine; 

class Window
{

private:
    uint16 width; 
    uint16 height; 
    
public:
    Window();
    
    
    void CreateWindow(uint16 width, uint16 height);
    
    
};
