#include "Sprite/Texture.hpp"

void Texture::Load ()
{
    stbi_set_flip_vertically_on_load(1);
    Buffer = stbi_load(FilePath.c_str(), &Width, &Height, &Chanel, 4);

    glGenTextures(1, &TextureId);
    glBindTexture(GL_TEXTURE_2D, TextureId);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, Width, Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, Buffer);
    glBindTexture(GL_TEXTURE_2D, 0);

    if (Buffer)
        stbi_image_free(Buffer);
}