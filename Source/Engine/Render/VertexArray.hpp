#pragma once

#include "glad/glad.h"
#include "Render/VertexBuffer.hpp"

enum class VertexLayout : GLuint
{
    Position = 0,
    TexCoord = 1,
    Color = 2
};

class VertexArray
{
private:
    GLuint VertexArrayId = 0;

public:
    VertexArray () = default;

    ~VertexArray ()
    {
        Unbind();
        Unload();
    }

    void Load ()
    {
        if (VertexArrayId)
            return;
        
        glGenVertexArrays(1, &VertexArrayId);
    }

    void Unload ()
    {
        if (!VertexArrayId)
            return;
        
        glDeleteVertexArrays(1, &VertexArrayId);
        VertexArrayId = 0;
    }

    void Bind ()
    {
        if (!VertexArrayId)
            return;
        
        glBindVertexArray(VertexArrayId);
    }

    void Unbind ()
    {
        if (!VertexArrayId)
            return;
        
        glBindVertexArray(0);
    }

    void AttachVertex(unsigned int VertexBufferId, VertexLayout Layout, GLint Size, GLenum Type, GLboolean Normalized, GLsizei Stride, size_t Offset)
    {
        if (!VertexArrayId)
            return;
        
        VertexBuffer::Bind(VertexBufferId);

        glEnableVertexAttribArray(static_cast<GLuint>(Layout));

        glVertexAttribPointer(
            static_cast<GLuint>(Layout),
            Size,
            Type,
            Normalized,
            Stride,
            reinterpret_cast<void*>(Offset)
        );
    }
};