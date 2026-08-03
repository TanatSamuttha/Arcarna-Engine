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
    static unsigned int Create (std::vector<float>& Vertices)
    {
        unsigned int Id = Buffers.size();
        if (!FreeIds.empty())
        {
            Id = FreeIds.back();
            FreeIds.pop_back();
            Buffers[Id] = std::make_unique<VertexBuffer>(Vertices);
        }
        else
        {
            Buffers.push_back(std::make_unique<VertexBuffer>(Vertices));
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
        glBindBuffer(GL_ARRAY_BUFFER, 0);
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
    }

    VertexBuffer(const VertexBuffer&) = delete;
    VertexBuffer& operator=(const VertexBuffer&) = delete;

private:
    unsigned int Id;
    GLuint VertexBufferId = 0;
    std::vector<float> Vertices;

    void Load ()
    {
        if (VertexBufferId)
            return;
        
        glGenBuffers(1, &VertexBufferId);
        glBindBuffer(GL_ARRAY_BUFFER, VertexBufferId);
        glBufferData(GL_ARRAY_BUFFER, Vertices.size() * sizeof(float), Vertices.data(), GL_STATIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    void Unload ()
    {
        if (!VertexBufferId)
            return;
        
        glDeleteBuffers(1, &VertexBufferId);
        VertexBufferId = 0;
    }

    void Bind ()
    {
        if (!VertexBufferId)
            return;
        
        glBindBuffer(GL_ARRAY_BUFFER, VertexBufferId);
    }

    std::vector<float>& GetVertices ()
    {
        return Vertices;
    }
};