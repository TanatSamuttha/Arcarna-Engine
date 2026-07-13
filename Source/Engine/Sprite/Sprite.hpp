#pragma once

#include <stdexcept>

class Sprite
{
public:
    unsigned int Width;
    unsigned int Height;

    Sprite (unsigned int Width, unsigned int Height) : Width(Width), Height(Height) {}
};