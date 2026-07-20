#pragma once

#include <vector>
#include <memory>

#include "glad/glad.h"

class VertexBuffer
{
private:
    inline static std::vector<std::unique_ptr<VertexBuffer>> Buffers;
    inline static std::vector<unsigned int> FreeIds;

public:
    static unsigned int Create (const std::string& FilePath)
    {
        unsigned int Id = Buffers.size();
        if (!FreeIds.empty())
        {
            Id = FreeIds.back();
            FreeIds.pop_back();
            Buffers[Id] = std::make_unique<VertexBuffer>(Id, FilePath);
        }
        else
        {
            Buffers.push_back(std::make_unique<VertexBuffer>(Id, FilePath));
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

    static GLuint GetVertexBufferId (unsigned int Id)
    {
        return Buffers[Id]->GetVertexBufferId();
    }

    static std::vector<float>& GetVertices (unsigned int Id)
    {
        return Buffers[Id]->GetVertices();
    }

public:
    VertexBuffer (std::vector<float> Vertices) : Vertices(Vertices) {}
    
    ~VertexBuffer ()
    {
        Unload();
        Unbind();
    }

private:
    GLuint VertexBufferId = 0;
    std::vector<float> Vertices;

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

    GLuint64 GetVertexBufferId ()
    {
        return VertexBufferId;
    }

    std::vector<float>& GetVertices ()
    {
        return Vertices;
    }
};