#pragma once

#include <stdexcept>

#include "Mesh/Mesh.hpp"
#include "Texture/Texture2D.hpp"

class Sprite
{
public:
    unsigned int MeshId;
    unsigned int TextureId;

    Sprite (unsigned int TextureId) :
    MeshId(Mesh::QuadId), TextureId(TextureId) {}
};