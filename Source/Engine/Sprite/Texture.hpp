#pragma once

#include <string>

#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "stb_image.h"

class Texture
{
private:
    GLuint TextureId;
    std::string FilePath;
    unsigned char* Buffer;
    int Width = 0, Height = 0, Chanel = 0;

public:
    Texture (std::string& FilePath) : FilePath(FilePath) {}

    void Load ();

    void Unload ();
};