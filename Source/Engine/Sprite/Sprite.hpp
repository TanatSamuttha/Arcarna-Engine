#pragma once

#include <stdexcept>

class Sprite
{
public:
    unsigned int Width;
    unsigned int Height;
    unsigned int Texture;

    bool Active = true;

    Sprite (unsigned int Width, unsigned int Height) : Width(Width), Height(Height) {}
};