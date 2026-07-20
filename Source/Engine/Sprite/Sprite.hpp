#pragma once

#include <stdexcept>

#include "Render/Texture2D.hpp"

class Sprite
{
public:
    unsigned int Width = 0;
    unsigned int Height = 0;
    Texture2D SpriteTexture;

    bool Active = true;

    Sprite (const std::string& FilePath) : SpriteTexture(std::move(Texture2D(FilePath)))
    {
        Width = SpriteTexture.GetWidth();
        Height = SpriteTexture.GetHeight();
    }

    Sprite (unsigned int Width, unsigned int Height, std::string FilePath) : 
    Width(Width), Height(Height), SpriteTexture(std::move(Texture2D(FilePath))) {}
};