#pragma once

#include <vector>
#include <string>
#include <memory>

#include "glad/glad.h"
#include "stb_image.h"

class Texture2D
{
private:
    static std::vector<std::unique_ptr<Texture2D>> Textures;
    static std::vector<unsigned int> FreeIds;

public:
    static unsigned int Create (const std::string& FilePath)
    {
        unsigned int Id = Textures.size();
        if (!FreeIds.empty())
        {
            Id = FreeIds.back();
            FreeIds.pop_back();
            Textures[Id] = std::make_unique<Texture2D>(Id, FilePath);
        }
        else
        {
            Textures.push_back(std::make_unique<Texture2D>(Id, FilePath));
        }

        return Id;
    }

    static void Delete (unsigned int Id)
    {
        Textures[Id].reset();
        FreeIds.push_back(Id);
    }

    static void Load (unsigned int Id)
    {
        Textures[Id]->Load();
    }

    static void Unload (unsigned int Id)
    {
        Textures[Id]->Unload();
    }

    static void Bind (unsigned int Id)
    {
        Textures[Id]->Bind();
    }

    static void Unbind (unsigned int Id)
    {
        Textures[Id]->Unbind();
    }

    static GLuint GetTextureId (unsigned int Id)
    {
        return Textures[Id]->GetTextureId();
    }

    static unsigned int GetWidth (unsigned int Id)
    {
        return Textures[Id]->GetWidth();
    }

    static unsigned int GetHeight (unsigned int Id)
    {
        return Textures[Id]->GetHeight();
    }

private:
    unsigned int Id;
    GLuint TextureId = 0;
    int Width = 0, Height = 0, Chanel = 0;

    std::string FilePath;

    Texture2D (const unsigned int Id, const std::string& FilePath) : Id(Id), FilePath(FilePath) {}

    ~Texture2D ()
    {
        Unbind();
        Unload();
    }

    Texture2D(const Texture2D&) = delete;
    Texture2D& operator=(const Texture2D&) = delete;

    void Load ()
    {
        if (TextureId) 
            return;

        stbi_set_flip_vertically_on_load(1);
        unsigned char* Buffer =  stbi_load(FilePath.c_str(), &Width, &Height, &Chanel, 4);

        if (!Buffer)
            throw std::runtime_error("Failed to load texture");

        glGenTextures(1, &TextureId);
        glBindTexture(GL_TEXTURE_2D, TextureId);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, Width, Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, Buffer);
        glBindTexture(GL_TEXTURE_2D, 0);

        stbi_image_free(Buffer);
        Buffer = nullptr;
    }

    void Unload ()
    {
        if (!TextureId)
            return;
        
        glDeleteTextures(1, &TextureId);
        TextureId = 0;
    }

    void Bind ()
    {
        if (!TextureId)
            return;

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, TextureId);
    }

    void Unbind ()
    {
        if (TextureId)
            glBindTexture(GL_TEXTURE_2D, 0);
    }

    unsigned int GetId ()
    {
        return Id;
    }

    GLuint GetTextureId ()
    {
        return TextureId;
    }

    unsigned int GetWidth ()
    {
        return Width;
    }

    unsigned int GetHeight ()
    {
        return Height;
    }
};