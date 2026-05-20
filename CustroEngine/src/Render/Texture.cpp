#include "Texture.h"

#include <glad/glad.h>

#include "utils/stb_image.h"

std::map<const String, Texture*> Texture::AllTexturesMap;

Texture::Texture(String path, String name)
{
    glGenTextures(1, &ID);
    glBindTexture(GL_TEXTURE_2D, ID);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    unsigned char *data = stbi_load(path.CStr(), &Width, &Height, &Channels, 0);
    GLenum format = (Channels == 4) ? GL_RGBA : GL_RGB;
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, format, Width, Height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
        delete this;
    }
    
    stbi_image_free(data);
    
    AllTexturesMap[name] = this;
}

Texture::~Texture()
{
    glDeleteTextures(1, &ID);
    AllTexturesMap.erase(Name);
}

Texture* Texture::GetTextureByName(const String name)
{
    auto it = AllTexturesMap.find(name);
    if (it != AllTexturesMap.end())
        return it->second;
    return nullptr;
}
