#pragma once

#include "Sprite/Sprite.hpp"

class Renderer
{
public:
    unsigned int MeshId;
    unsigned int MeshNumber;
    unsigned int Texture2DId;

    Renderer (Sprite& sprite) :
    MeshId(sprite.MeshId), MeshNumber(1), Texture2DId(sprite.TextureId) {}
};