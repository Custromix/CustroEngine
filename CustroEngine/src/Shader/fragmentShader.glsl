#version 330 core
out vec4 FragColor;

in vec2 TextureCoordinate;

uniform sampler2D Texture;

void main()
{
    if(TextureCoordinate == vec2(0, 0))
        FragColor = vec4(1.0f, 1.0f, 1.0f, 1.0f) * texture(Texture, TextureCoordinate);
    else
        FragColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);
} 