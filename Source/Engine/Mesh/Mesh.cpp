#include "Mesh/Mesh.hpp"

void Mesh::Start ()
{
    std::vector<float> vertices = {
        -0.5f, -0.5f,
        0.5f,  -0.5f,
        0.5f,   0.5f,
        -0.5f,  0.5f
    };

    std::vector<unsigned int> indexes = {
        0, 1, 2,
        2, 3, 0
    };

    VertexArray vao;
    vao.Load();
    vao.Bind();

    unsigned int vboId = VertexBuffer::Create(vertices);
    VertexBuffer::Load(vboId);
    vao.AttachVertex(vboId, VertexLayout::Position, 2, GL_FLOAT, false, 2 * sizeof(float), 0);

    unsigned int iboId = IndexBuffer::Create(indexes);
    IndexBuffer::Load(iboId);

    vao.Unbind();

    Mesh::Create(vboId, vao, iboId);
    Mesh::Load(Mesh::QuadId);
}