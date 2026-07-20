#pragma once

#include <stdexcept>

#include "Texture/Texture2D.hpp"

class Sprite
{
public:
    unsigned int Width = 0;
    unsigned int Height = 0;
    unsigned int SpriteTextureId;

    bool Active = true;

    Sprite (const unsigned int SpriteTextureId) : SpriteTextureId(SpriteTextureId)
    {
        Width = Texture2D::GetWidth(SpriteTextureId);
        Height = Texture2D::GetHeight(SpriteTextureId);
    }

    Sprite (unsigned int Width, unsigned int Height, const unsigned int SpriteTextureId) : 
    Width(Width), Height(Height), SpriteTextureId(SpriteTextureId) {}
};