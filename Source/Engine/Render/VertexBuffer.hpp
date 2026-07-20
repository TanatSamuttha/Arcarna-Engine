#pragma once

#include <vector>

#include "glad/glad.h"

class VertexBuffer
{
private:
    GLuint VertexBufferId = 0;

public:
    std::vector<float> Vertices;

    VertexBuffer (std::vector<float> Vertices) : Vertices(Vertices) {}

    ~VertexBuffer ()
    {
        Unload();
        Unbind();
    }

    void Load ()
    {
        glGenBuffers(1, &VertexBufferId);
        glBindBuffer(GL_ARRAY_BUFFER, VertexBufferId);
        glBufferData(GL_ARRAY_BUFFER, Vertices.size() * sizeof(float), Vertices.data(), GL_STATIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    void Unload ()
    {
        glDeleteBuffers(1, &VertexBufferId);
    }

    void Bind ()
    {
        glBindBuffer(GL_ARRAY_BUFFER, VertexBufferId);
    }

    void Unbind ()
    {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }
};