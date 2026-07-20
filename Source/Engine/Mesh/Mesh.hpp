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
    static unsigned int Create (unsigned int VertexBufferId, VertexArray& VertexArrayObject, unsigned int IndexBufferId)
    {
        unsigned int Id = Buffers.size();
        if (!FreeIds.empty())
        {
            Id = FreeIds.back();
            FreeIds.pop_back();
            Buffers[Id] = std::make_unique<Mesh>(VertexBufferId, VertexArrayObject, IndexBufferId);
        }
        else
        {
            Buffers.push_back(std::make_unique<Mesh>(VertexBufferId, VertexArrayObject, IndexBufferId));
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

    Mesh (unsigned int VertexBufferId, VertexArray& VertexArrayObject, unsigned int IndexBufferId) :
    VertexBufferId(VertexBufferId), VertexArrayObject(VertexArrayObject), IndexBufferId(IndexBufferId) {}

    Mesh(const Mesh&) = delete;
    Mesh& operator=(const Mesh&) = delete;

private:
    unsigned int VertexBufferId = 0;
    unsigned int IndexBufferId = 0;
    VertexArray VertexArrayObject;

    void Load ()
    {
        VertexBuffer::Load(VertexBufferId);
        VertexArrayObject.Load();
        IndexBuffer::Load(IndexBufferId);
    }

    void Unload ()
    {
        VertexBuffer::Unload(VertexBufferId);
        VertexArrayObject.Unload();
        IndexBuffer::Unload(IndexBufferId);
    }

    void Bind ()
    {
        VertexBuffer::Bind(VertexBufferId);
        VertexArrayObject.Bind();
        IndexBuffer::Bind(IndexBufferId);
    }

    void Unbind ()
    {
        VertexBuffer::Unbind(VertexBufferId);
        VertexArrayObject.Unbind();
        IndexBuffer::Unbind(IndexBufferId);
    }
};