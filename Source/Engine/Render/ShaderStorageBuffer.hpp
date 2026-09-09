#pragma once

#include <vector>
#include <memory>

#include "glad/glad.h"

class BuiltinSSBO
{
public:
    static GLuint TransformId;
    static const GLuint TransformBinding = 0;
};

class ShaderStorageBuffer
{
private:
    inline static std::vector<std::unique_ptr<ShaderStorageBuffer>> Buffers;
    inline static std::vector<unsigned int> FreeIds;

public:
    static unsigned int Create (unsigned int Binding)
    {
        unsigned int Id = Buffers.size();
        if (!FreeIds.empty())
        {
            Id = FreeIds.back();
            FreeIds.pop_back();
            Buffers[Id] = std::make_unique<ShaderStorageBuffer>(Binding);
        }
        else
        {
            Buffers.push_back(std::make_unique<ShaderStorageBuffer>(Binding));
        }

        return Id;
    }

    static void CreateTransform ()
    {
        Create(BuiltinSSBO::TransformBinding);
    }

    static void Delete (unsigned int Id)
    {
        Buffers[Id].reset();
        FreeIds.push_back(Id);
    }

    static void Load (unsigned int Id, std::vector<float> Data)
    {
        Buffers[Id]->Load(Data);
    }

    static void Unload (unsigned int Id)
    {
        Buffers[Id]->Unload();
    }

    static void Bind (unsigned int Id)
    {
        Buffers[Id]->Bind();
    }

    static void Unbind ()
    {
        glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
    }

    static std::vector<float>& GetData (unsigned int Id)
    {
        return Buffers[Id]->GetData();
    }

    static size_t Size (unsigned int Id)
    {
        return Buffers[Id]->Size();
    }

public:
    ShaderStorageBuffer (unsigned int Binding) : Binding(Binding)
    {
        glGenBuffers(1, &StorageBufferId);
        glBindBuffer(GL_SHADER_STORAGE_BUFFER, StorageBufferId);
        glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
    }
    
    ~ShaderStorageBuffer ()
    {
        Unload();
    }

    ShaderStorageBuffer(const ShaderStorageBuffer&) = delete;
    ShaderStorageBuffer& operator=(const ShaderStorageBuffer&) = delete;

private:
    unsigned int Binding;
    GLuint StorageBufferId = 0;
    unsigned int size = 0;
    std::vector<float> Data;

    void Load (std::vector<float> &Data)
    {
        this->Data = std::move(Data);
        if (!StorageBufferId)
            return;
        
        Bind();
        if (this->Data.size() != size)
        {
            size = this->Data.size();
            glBufferData(GL_SHADER_STORAGE_BUFFER, sizeof(float) * this->Data.size(), this->Data.data(), GL_DYNAMIC_DRAW);
        }
        else
            glBufferSubData(GL_SHADER_STORAGE_BUFFER, 0, sizeof(float) * this->Data.size(), this->Data.data());
    }

    void Unload ()
    {
        if (!StorageBufferId)
            return;
        
        glDeleteBuffers(1, &StorageBufferId);
        StorageBufferId = 0;
    }

    void Bind ()
    {
        if (!StorageBufferId)
            return;

        glBindBufferBase(GL_SHADER_STORAGE_BUFFER, Binding, StorageBufferId);
        glBindBuffer(GL_SHADER_STORAGE_BUFFER, StorageBufferId);
    }

    std::vector<float>& GetData ()
    {
        return Data;
    }

    size_t Size ()
    {
        return Data.size();
    }
};