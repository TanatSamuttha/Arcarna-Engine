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
    VertexArray ()
    {
        glGenVertexArrays(1, &VertexArrayId);
    }

    ~VertexArray ()
    {
        glDeleteVertexArrays(1, &VertexArrayId);
    }

    void Bind ()
    {
        glBindVertexArray(VertexArrayId);
    }

    void Unbind ()
    {
        glBindVertexArray(0);
    }

    void AttachVertex(VertexBuffer& vbo, VertexLayout Layout, GLint Size, GLenum Type, GLboolean Normalized, GLsizei Stride, size_t Offset)
    {
        vbo.Bind();

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