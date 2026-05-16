#version 330 core

layout (location = 0) in vec3 meshInitialPos;

uniform mat4 Transform;

void main()
{
   gl_Position = Transform * vec4(meshInitialPos, 1.0f);
}
