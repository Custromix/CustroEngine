#include "Input.h"

#include "Window.h"

GLFWwindow* Input::Window;

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
