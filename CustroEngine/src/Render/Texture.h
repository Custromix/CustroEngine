#pragma once

#include <map>

#include "types.hpp"
#include "utils/String.h"

using namespace Engine;

class Texture
{
public:
    Texture(String path, String name);
    ~Texture();
    
    static Texture* GetTextureByName(const String name);
    
    uint32 GetID() { return ID; }

private:
    uint32 ID;
    
    int32 Width, Height, Channels;
    
    String Name;
    
    static std::map<const String, Texture*> AllTexturesMap;
};
