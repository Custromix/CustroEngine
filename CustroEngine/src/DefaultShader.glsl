uniform sampler2D aTexture;

void Shader()
{
    BaseColor = mix(texture(aTexture, TexCoord), vec4(1.0f, 0.7f, 1.0f, 1.0f), 0.2);
}