#pragma once

#include <vector>
#include <memory>

#include "Render/VertexBuffer.hpp"
#include "Render/VertexArray.hpp"
#include "Render/IndexBuffer.hpp"
#include "Render/Shader.hpp"

enum class BuiltinMesh : unsigned int
{
    QuadId = 0
};

class Mesh
{
private:
    inline static std::vector<std::unique_ptr<Mesh>> Buffers;
    inline static std::vector<unsigned int> FreeIds;
    
public:

    static void Start ();

    static unsigned int Create (unsigned int VertexBufferId, unsigned int VertexArrayId, unsigned int IndexBufferId, BuiltinShader ProgramId)
    {
        return Create(VertexBufferId, VertexArrayId, IndexBufferId, static_cast<unsigned int>(ProgramId));
    }

    static unsigned int Create (unsigned int VertexBufferId, unsigned int VertexArrayId, unsigned int IndexBufferId, unsigned int ProgramId)
    {
        unsigned int Id = Buffers.size();
        if (!FreeIds.empty())
        {
            Id = FreeIds.back();
            FreeIds.pop_back();
            Buffers[Id] = std::make_unique<Mesh>(VertexBufferId, VertexArrayId, IndexBufferId, ProgramId);
        }
        else
        {
            Buffers.push_back(std::make_unique<Mesh>(VertexBufferId, VertexArrayId, IndexBufferId, ProgramId));
        }

        return Id;
    }

    static void Delete (unsigned int Id)
    {
        Buffers[Id].reset();
        FreeIds.push_back(Id);
    }

    static void Delete (BuiltinMesh Id)
    {
        Buffers[static_cast<unsigned int>(Id)].reset();
        FreeIds.push_back(static_cast<unsigned int>(Id));
    }

    static void Load (unsigned int Id)
    {
        Buffers[Id]->Load();
    }

    static void Load (BuiltinMesh Id)
    {
        Buffers[static_cast<unsigned int>(Id)]->Load();
    }

    static void Unload (unsigned int Id)
    {
        Buffers[Id]->Unload();
    }

    static void Unload (BuiltinMesh Id)
    {
        Buffers[static_cast<unsigned int>(Id)]->Unload();
    }

    static void Bind (unsigned int Id)
    {
        Buffers[Id]->Bind();
    }

    static void Bind (BuiltinMesh Id)
    {
        Buffers[static_cast<unsigned int>(Id)]->Bind();
    }

    static void Unbind (unsigned int Id)
    {
        Buffers[Id]->Unbind();
    }

    static void Unbind (BuiltinMesh Id)
    {
        Buffers[static_cast<unsigned int>(Id)]->Unbind();
    }

    static unsigned int GetVertexBufferId (unsigned int Id)
    {
        return Buffers[Id]->VertexBufferId;
    }

    static unsigned int GetVertexArrayId (unsigned int Id)
    {
        return Buffers[Id]->VertexArrayId;
    }

    static unsigned int GetIndexBufferId (unsigned int Id)
    {
        return Buffers[Id]->IndexBufferId;
    }

    Mesh (unsigned int VertexBufferId, unsigned int VertexArrayId, unsigned int IndexBufferId, unsigned int ProgramId) :
    VertexBufferId(VertexBufferId), VertexArrayId(VertexArrayId), IndexBufferId(IndexBufferId), ProgramId(ProgramId) {}

    Mesh(const Mesh&) = delete;
    Mesh& operator=(const Mesh&) = delete;

private:
    unsigned int VertexBufferId = -1;
    unsigned int VertexArrayId = -1;
    unsigned int IndexBufferId = -1;
    unsigned int ProgramId = -1;

    void Load ()
    {
        VertexBuffer::Load(VertexBufferId);
        VertexArray::Load(VertexArrayId);
        IndexBuffer::Load(IndexBufferId);
        Shader::Load(ProgramId);
    }

    void Unload ()
    {
        VertexBuffer::Unload(VertexBufferId);
        VertexArray::Unload(VertexArrayId);
        IndexBuffer::Unload(IndexBufferId);
        Shader::Unload(ProgramId);
    }

    void Bind ()
    {
        VertexBuffer::Bind(VertexBufferId);
        VertexArray::Bind(VertexArrayId);
        IndexBuffer::Bind(IndexBufferId);
        Shader::Bind(ProgramId);
    }

    void Unbind ()
    {
        VertexBuffer::Unbind();
        VertexArray::Unbind();
        IndexBuffer::Unbind();
        Shader::Unbind();
    }
};