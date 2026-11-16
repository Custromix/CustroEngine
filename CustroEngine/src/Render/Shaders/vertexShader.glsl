#version 330 core

layout (location = 0) in vec3 InitialPos;
layout (location = 1) in vec2 TextCoord;
layout (location = 2) in vec3 aNormals;
layout (location = 3) in vec4 right;
layout (location = 4) in vec4 top;
layout (location = 5) in vec4 forward;
layout (location = 6) in vec4 pos;

out vec2 TextureCoordinate;
out vec3 Normals;

//uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
 
uniform mat4 MVP;

void main()
{
    mat4 model = mat4(right, top, forward, pos);
    gl_Position = projection * view * model * vec4(InitialPos, 1.0f);
    TextureCoordinate = TextCoord;
    Normals = aNormals;
}