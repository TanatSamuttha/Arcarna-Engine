#pragma once

#include <vector>
#include <memory>

#include "Render/VertexBuffer.hpp"
#include "Render/VertexArray.hpp"
#include "Render/IndexBuffer.hpp"

class Mesh
{
private:
    inline static std::vector<std::unique_ptr<Mesh>> Buffers;
    inline static std::vector<unsigned int> FreeIds;
    
public:
    inline static constexpr unsigned int QuadId = 0;

    static void Start ();

    static unsigned int Create (unsigned int VertexBufferId, unsigned int VertexArrayId, unsigned int IndexBufferId)
    {
        unsigned int Id = Buffers.size();
        if (!FreeIds.empty())
        {
            Id = FreeIds.back();
            FreeIds.pop_back();
            Buffers[Id] = std::make_unique<Mesh>(VertexBufferId, VertexArrayId, IndexBufferId);
        }
        else
        {
            Buffers.push_back(std::make_unique<Mesh>(VertexBufferId, VertexArrayId, IndexBufferId));
        }

        return Id;
    }

    static void Delete (unsigned int Id)
    {
        Buffers[Id].reset();
        FreeIds.push_back(Id);
    }

    static void Load (unsigned int Id)
    {
        Buffers[Id]->Load();
    }

    static void Unload (unsigned int Id)
    {
        Buffers[Id]->Unload();
    }

    static void Bind (unsigned int Id)
    {
        Buffers[Id]->Bind();
    }

    static void Unbind (unsigned int Id)
    {
        Buffers[Id]->Unbind();
    }

    Mesh (unsigned int VertexBufferId, unsigned int VertexArrayId, unsigned int IndexBufferId) :
    VertexBufferId(VertexBufferId), VertexArrayId(VertexArrayId), IndexBufferId(IndexBufferId) {}

    Mesh(const Mesh&) = delete;
    Mesh& operator=(const Mesh&) = delete;

private:
    unsigned int VertexBufferId = -1;
    unsigned int VertexArrayId = -1;
    unsigned int IndexBufferId = -1;

    void Load ()
    {
        VertexBuffer::Load(VertexBufferId);
        VertexArray::Load(VertexArrayId);
        IndexBuffer::Load(IndexBufferId);
    }

    void Unload ()
    {
        VertexBuffer::Unload(VertexBufferId);
        VertexArray::Unload(VertexArrayId);
        IndexBuffer::Unload(IndexBufferId);
    }

    void Bind ()
    {
        VertexBuffer::Bind(VertexBufferId);
        VertexArray::Bind(VertexArrayId);
        IndexBuffer::Bind(IndexBufferId);
    }

    void Unbind ()
    {
        VertexBuffer::Unbind(VertexBufferId);
        VertexArray::Unbind(VertexArrayId);
        IndexBuffer::Unbind(IndexBufferId);
    }
};