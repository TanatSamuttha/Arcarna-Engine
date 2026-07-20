#pragma once

#include "glad/glad.h"
#include "Render/VertexBuffer.hpp"

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

    void AttachVertex(VertexBuffer& vbo, GLuint Layout, GLint Size, GLenum Type, GLboolean Normalized, GLsizei Stride, size_t Offset)
    {
        vbo.Bind();

        glEnableVertexAttribArray(Layout);

        glVertexAttribPointer(
            Layout,
            Size,
            Type,
            Normalized,
            Stride,
            reinterpret_cast<void*>(Offset)
        );
    }
};