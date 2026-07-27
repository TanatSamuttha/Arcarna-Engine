#pragma once

#include <vector>
#include <memory>

#include "glad/glad.h"

class IndexBuffer
{
private:
    inline static std::vector<std::unique_ptr<IndexBuffer>> Buffers;
    inline static std::vector<unsigned int> FreeIds;

public:
    static unsigned int Create (std::vector<unsigned int>& Indexes)
    {
        unsigned int Id = Buffers.size();
        if (!FreeIds.empty())
        {
            Id = FreeIds.back();
            FreeIds.pop_back();
            Buffers[Id] = std::make_unique<IndexBuffer>(Indexes);
        }
        else
        {
            Buffers.push_back(std::make_unique<IndexBuffer>(Indexes));
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

    static GLuint GetIndexBufferId (unsigned int Id)
    {
        return Buffers[Id]->GetIndexBufferId();
    }

    static std::vector<unsigned int>& GetIndexes (unsigned int Id)
    {
        return Buffers[Id]->GetIndexes();
    }

    static size_t Size (unsigned int Id)
    {
        return Buffers[Id]->Size();
    }

public:
    IndexBuffer (std::vector<unsigned int> Indexes) : Indexes(Indexes) {}
    
    ~IndexBuffer ()
    {
        Unbind();
        Unload();
    }

    IndexBuffer(const IndexBuffer&) = delete;
    IndexBuffer& operator=(const IndexBuffer&) = delete;

private:
    GLuint IndexBufferId = 0;
    std::vector<unsigned int> Indexes;

    void Load ()
    {
        if (IndexBufferId)
            return;
        
        glGenBuffers(1, &IndexBufferId);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IndexBufferId);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, Indexes.size() * sizeof(unsigned int), Indexes.data(), GL_STATIC_DRAW);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

    void Unload ()
    {
        if (!IndexBufferId)
            return;
        
        glDeleteBuffers(1, &IndexBufferId);
        IndexBufferId = 0;
    }

    void Bind ()
    {
        if (!IndexBufferId)
            return;
        
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IndexBufferId);
    }

    void Unbind ()
    {
        if (!IndexBufferId)
            return;
        
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

    GLuint GetIndexBufferId ()
    {
        return IndexBufferId;
    }

    std::vector<unsigned int>& GetIndexes ()
    {
        return Indexes;
    }

    size_t Size ()
    {
        return Indexes.size();
    }
};