#pragma once

#include <string>

#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "stb_image.h"

class Texture
{
private:
    GLuint TextureId;
    unsigned char* Buffer;
    int Chanel = 0;

public:
    std::string FilePath;
    int Width = 0, Height = 0;

    Texture (std::string& FilePath) : FilePath(FilePath) {}

    ~Texture ()
    {
        Unload();
    }

    void Load ();

    void Unload ()
    {
        glDeleteTextures(1, &TextureId);
    }

    void Bind ()
    {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, TextureId);
    }

    void Unbind ()
    {
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    GLuint GetTextureId ()
    {
        return TextureId;
    }
};