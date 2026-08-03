#pragma once

#include <vector>
#include <memory>
#include <fstream>
#include <sstream>
#include <iostream>

#include "glad/glad.h"

class Shader
{
private:
    inline static std::vector<std::unique_ptr<Shader>> Shaders;
    inline static std::vector<unsigned int> FreeIds;

public:
    static unsigned int Create (const std::string& FilePath)
    {
        unsigned int Id = Shaders.size();
        if (!FreeIds.empty())
        {
            Id = FreeIds.back();
            FreeIds.pop_back();
            Shaders[Id] = std::make_unique<Shader>(FilePath);
        }
        else
        {
            Shaders.push_back(std::make_unique<Shader>(FilePath));
        }

        return Id;
    }

    static void Delete (unsigned int Id)
    {
        Shaders[Id].reset();
        FreeIds.push_back(Id);
    }

    static void Load (unsigned int Id)
    {
        Shaders[Id]->Load();
    }

    static void Unload (unsigned int Id)
    {
        Shaders[Id]->Unload();
    }

    static void Bind (unsigned int Id)
    {
        Shaders[Id]->Bind();
    }
    
    static void Unbind ()
    {
        glUseProgram(0);
    }

public:
    Shader (const std::string& VertexFilePath, const std::string& FragmentFilePath) : 
    VertexFilePath(VertexFilePath), FragmentFilePath(FragmentFilePath) {};

    ~Shader ()
    {
        Unload();
    }

    Shader(const Shader&) = delete;
    Shader& operator=(const Shader&) = delete;

private:
    GLuint ProgramId = 0;
    std::string VertexFilePath;
    std::string FragmentFilePath;

    inline std::string ReadShader (std::string& FilePath)
    {
        std::ifstream file;

        file.exceptions(std::ifstream::failbit | std::ifstream::badbit);

        try
        {
            file.open(FilePath);

            std::stringstream shaderStream;
            shaderStream << file.rdbuf();

            file.close();

            return std::move(shaderStream.str());
        }
        catch (std::ifstream::failure& e)
        {
            std::cout << "Error read shader file fail" << FilePath << '\n';

            return "";
        }
    }

    inline GLuint CompileShader (unsigned int type, const char* source)
    {
        GLuint shaderId = glCreateShader(type);
        glShaderSource(shaderId, 1, &source, nullptr);
        glCompileShader(shaderId);

        GLint result;
        glGetShaderiv(shaderId, GL_COMPILE_STATUS, &result);
        if (result == GL_FALSE)
        {
            int length;
            glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &length);
            char log[length];
            glGetShaderInfoLog(shaderId, length, &length, log);

            std::cout << (type == GL_FRAGMENT_SHADER? "Fragment" : "Vertex") << "shader compile error " << log << '\n';
            glDeleteShader(shaderId);
        }

        return shaderId;
    }

    void Load ()
    {
        if (ProgramId)
            return;

        ProgramId = glCreateProgram();
        GLuint VertexId = CompileShader(GL_VERTEX_SHADER, ReadShader(VertexFilePath).c_str());
        GLuint FragmentId = CompileShader(GL_FRAGMENT_SHADER, ReadShader(FragmentFilePath).c_str());

        glAttachShader(ProgramId, VertexId);
        glAttachShader(ProgramId, FragmentId);
        glLinkProgram(ProgramId);

        glDeleteShader(VertexId);
        glDeleteShader(FragmentId);
    }

    void Unload ()
    {
        if (!ProgramId)
            return;
        
        glDeleteProgram(ProgramId);
    }

    void Bind ()
    {
        if (!ProgramId)
            return;

        glUseProgram(ProgramId);
    }
};