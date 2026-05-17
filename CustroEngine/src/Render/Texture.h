#pragma once

#include "types.hpp"
#include "utils/String.h"

using namespace Engine;

class Texture
{
public:
    Texture(String path, String name = "");
    ~Texture();

private:
    uint32 ID;
    
    int32 Width, Height, Channels;
    
    String Name;
    
};
