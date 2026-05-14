#version 330 core

out vec4 FragColor;

in vec4 ourColor;
in vec2 textCoord;

uniform vec3 otherColor;

uniform sampler2D Texture1;
uniform sampler2D Texture2;

uniform float AlphaBlend;

void main()
{
    if(otherColor == vec3(0,0,0))
    {
        //FragColor = texture(Texture2, textCoord);
        FragColor = mix(texture(Texture1, textCoord), texture(Texture2, textCoord), AlphaBlend);
    }
    else
    {
        FragColor = vec4(otherColor, 1.0);
    }
    
}