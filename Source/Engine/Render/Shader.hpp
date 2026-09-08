#pragma once

#include <vector>
#include <memory>
#include <fstream>
#include <sstream>
#include <iostream>

#include "glad/glad.h"
#include "Math/Math.hpp"
#include "Physics/Transform.hpp"
#include "Camera/Camera.hpp"

enum class BuiltinShader : unsigned int
{
    DefaultId = 0
};

class Shader
{
private:
    inline static std::vector<std::unique_ptr<Shader>> Shaders;
    inline static std::vector<unsigned int> FreeIds;

public:
    static unsigned int Create (const std::string& VertexFilePath, const std::string& FragmentFilePath)
    {
        unsigned int Id = Shaders.size();
        if (!FreeIds.empty())
        {
            Id = FreeIds.back();
            FreeIds.pop_back();
            Shaders[Id] = std::make_unique<Shader>(VertexFilePath, FragmentFilePath);
        }
        else
        {
            Shaders.push_back(std::make_unique<Shader>(VertexFilePath, FragmentFilePath));
        }

        return Id;
    }

    static void Delete (unsigned int Id)
    {
        Shaders[Id].reset();
        FreeIds.push_back(Id);
    }

    static void Delete (BuiltinShader Id)
    {
        Shaders[static_cast<unsigned int>(Id)].reset();
        FreeIds.push_back(static_cast<unsigned int>(Id));
    }

    static void Load (unsigned int Id)
    {
        Shaders[Id]->Load();
    }

    static void Load (BuiltinShader Id)
    {
        Shaders[static_cast<unsigned int>(Id)]->Load();
    }

    static void Unload (unsigned int Id)
    {
        Shaders[Id]->Unload();
    }

    static void Unload (BuiltinShader Id)
    {
        Shaders[static_cast<unsigned int>(Id)]->Unload();
    }

    static void Bind (unsigned int Id)
    {
        Shaders[Id]->Bind();
    }

    static void Bind (BuiltinShader Id)
    {
        Shaders[static_cast<unsigned int>(Id)]->Bind();
    }
    
    static void Unbind ()
    {
        glUseProgram(0);
    }

    static void SetRenderData (unsigned int Id, Transform& ModelTransform, Transform& CameraTransform, Camera& CameraData, const float& Aspect)
    {
        Shaders[Id]->SetRenderData(ModelTransform, CameraTransform, CameraData, Aspect);
    }

    static void SetRenderData (BuiltinShader Id, Transform& ModelTransform, Transform& CameraTransform, Camera& CameraData, const float& Aspect)
    {
        Shaders[static_cast<unsigned int>(Id)]->SetRenderData(ModelTransform, CameraTransform, CameraData, Aspect);
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
    GLint TextureLocation = -1;
    GLint RenderDataLocation = -1;

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
            std::cout << "Error read shader file fail " << FilePath << ' ' << e.what() << '\n';

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

        glUseProgram(ProgramId);

        TextureLocation = glGetUniformLocation(ProgramId, "u_Texture");
        glUniform1i(TextureLocation, 0);

        RenderDataLocation = glGetUniformLocation(ProgramId, "u_RenderData");
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

    void SetRenderData (Transform& ModelTransform, Transform& CameraTransform, Camera& CameraData, const float& Aspect)
    {
        float Buffer[17] = {
            ModelTransform.GetPosition().x,
            ModelTransform.GetPosition().y,
            ModelTransform.GetPosition().z,

            ModelTransform.GetScale().x,
            ModelTransform.GetScale().y,
            ModelTransform.GetScale().z,

            ModelTransform.GetRotation().x,
            ModelTransform.GetRotation().y,
            ModelTransform.GetRotation().z,

            CameraTransform.GetPosition().x,
            CameraTransform.GetPosition().y,
            CameraTransform.GetPosition().z,

            CameraTransform.GetRotation().x,
            CameraTransform.GetRotation().y,
            CameraTransform.GetRotation().z,

            CameraData.WidthScale,
            Aspect
        };
        glUniform1fv(RenderDataLocation, 17, Buffer);
    }
};