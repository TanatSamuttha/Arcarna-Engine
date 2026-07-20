#include "Render/VertexBuffer.hpp"

void VertexBuffer::Load ()
{
    glGenBuffers(1, &VertexBufferId);
    glBindBuffer(GL_ARRAY_BUFFER, VertexBufferId);
    glBufferData(GL_ARRAY_BUFFER, Vertices.size() * sizeof(float), Vertices.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}