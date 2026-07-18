#pragma once

#include <stdexcept>

#include "Sprite/Texture.hpp"

class Sprite
{
public:
    unsigned int Width;
    unsigned int Height;
    Texture TextureObject;

    bool Active = true;

    Sprite (unsigned int Width, unsigned int Height, std::string FilePath) : 
    Width(Width), Height(Height), TextureObject(std::move(Texture(FilePath))) {}
};