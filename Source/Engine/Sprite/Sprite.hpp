#pragma once

#include <stdexcept>

#include "Sprite/Texture.hpp"

class Sprite
{
public:
    unsigned int Width = 0;
    unsigned int Height = 0;
    Texture SpriteTexture;

    bool Active = true;

    Sprite (const std::string& FilePath) : SpriteTexture(std::move(Texture(FilePath)))
    {
        Width = SpriteTexture.GetWidth();
        Height = SpriteTexture.GetHeight();
    }

    Sprite (unsigned int Width, unsigned int Height, std::string FilePath) : 
    Width(Width), Height(Height), SpriteTexture(std::move(Texture(FilePath))) {}
};