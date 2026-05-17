#version 330 core

layout (location = 0) in vec3 InitialPos;
layout (location = 1) in vec2 TextCoord;
layout (location = 2) in vec3 Normals;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec2 TextureCoordinate;

void main()
{
   gl_Position = projection * view * model * vec4(InitialPos, 1.0f);
   TextureCoordinate = TextCoord;
}
