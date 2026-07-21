#include "Mesh/Mesh.hpp"

void Mesh::Start ()
{
    std::vector<float> vertices = {
        0.5f,   0.5f,
        -0.5f,  0.5f,
        -0.5f, -0.5f,
        0.5f,  -0.5f
    };

    std::vector<unsigned int> indexes = {
        0, 1, 2,
        2, 3, 0
    };

    unsigned int vaoId = VertexArray::Create();
    VertexArray::Load(vaoId);
    VertexArray::Bind(vaoId);

    unsigned int vboId = VertexBuffer::Create(vertices);
    VertexBuffer::Load(vboId);
    VertexArray::AttachVertex(vaoId, vboId, VertexLayout::Position, 2, GL_FLOAT, false, 2 * sizeof(float), 0);

    unsigned int iboId = IndexBuffer::Create(indexes);
    IndexBuffer::Load(iboId);

    VertexArray::Unbind(vaoId);

    Mesh::Create(vboId, vaoId, iboId);
    Mesh::Load(Mesh::QuadId);
}