#include "Utils.h"

#include <filesystem>

float Utils::NormalizeRGB(float rgb)
{
    return rgb/255.f;
}

String Utils::GetExePath()
{
    return std::filesystem::current_path().string().c_str();
}
