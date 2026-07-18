#pragma once

#include <stdexcept>

#include "Sprite/Texture.hpp"

class Sprite
{
public:
    unsigned int Width = 0;
    unsigned int Height = 0;
    Texture TextureObject;

    bool Active = true;

    Sprite (std::string FilePath) : TextureObject(std::move(Texture(FilePath)))
    {
        Width = TextureObject.GetWidth();
        Height = TextureObject.GetHeight();
    }

    Sprite (unsigned int Width, unsigned int Height, std::string FilePath) : 
    Width(Width), Height(Height), TextureObject(std::move(Texture(FilePath))) {}
};