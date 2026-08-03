#pragma once

#include <vector>
#include <memory>

#include "glad/glad.h"
#include "Render/VertexBuffer.hpp"

enum class VertexLayout : GLuint
{
    Position = 0,
    TexCoord = 1,
    Color = 2
};

class VertexArray
{
private:
    inline static std::vector<std::unique_ptr<VertexArray>> VertexArrays;
    inline static std::vector<unsigned int> FreeIds;

public:
    static unsigned int Create ()
    {
        unsigned int Id = VertexArrays.size();
        if (!FreeIds.empty())
        {
            Id = FreeIds.back();
            FreeIds.pop_back();
            VertexArrays[Id] = std::make_unique<VertexArray>();
        }
        else
        {
            VertexArrays.push_back(std::make_unique<VertexArray>());
        }

        return Id;
    }

    static void Delete (unsigned int Id)
    {
        VertexArrays[Id].reset();
        FreeIds.push_back(Id);
    }

public:
    VertexArray () = default;

    ~VertexArray ()
    {
        Unload();
    }

    VertexArray(const VertexArray&) = delete;
    VertexArray& operator=(const VertexArray&) = delete;

    static void Load (unsigned int Id)
    {
        VertexArrays[Id]->Load();
    }

    static void Unload (unsigned int Id)
    {
        VertexArrays[Id]->Unload();
    }

    static void Bind (unsigned int Id)
    {
        VertexArrays[Id]->Bind();
    }

    static void Unbind ()
    {
        glBindVertexArray(0);
    }

    static void AttachVertex (unsigned int Id, unsigned int VertexBufferId, VertexLayout Layout, GLint Size, GLenum Type, GLboolean Normalized, GLsizei Stride, size_t Offset)
    {
        VertexArrays[Id]->AttachVertex(VertexBufferId, Layout, Size, Type, Normalized, Stride, Offset);
    }

private:
    GLuint VertexArrayId = 0;

    void Load ()
    {
        if (VertexArrayId)
            return;
        
        glGenVertexArrays(1, &VertexArrayId);
    }

    void Unload ()
    {
        if (!VertexArrayId)
            return;
        
        glDeleteVertexArrays(1, &VertexArrayId);
        VertexArrayId = 0;
    }

    void Bind ()
    {
        if (!VertexArrayId)
            return;
        
        glBindVertexArray(VertexArrayId);
    }

    void AttachVertex(unsigned int VertexBufferId, VertexLayout Layout, GLint Size, GLenum Type, GLboolean Normalized, GLsizei Stride, size_t Offset)
    {
        if (!VertexArrayId)
            return;
        
        VertexBuffer::Bind(VertexBufferId);

        glEnableVertexAttribArray(static_cast<GLuint>(Layout));

        glVertexAttribPointer(
            static_cast<GLuint>(Layout),
            Size,
            Type,
            Normalized,
            Stride,
            reinterpret_cast<void*>(Offset)
        );
    }
};