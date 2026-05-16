#version 330 core

layout (location = 0) in vec3 InitialPos;

uniform mat4 model;
//meshInitialPos
void main()
{
   gl_Position = model * vec4(InitialPos, 1.0f);
}
