#pragma once

#include <map>
#include <stdexcept>

#include "Config.hpp"
#include "Camera/Camera.hpp"
#include "Scene/Scene.hpp"
#include "Render/Renderer.hpp"
#include "Physics/Transform.hpp"
#include "Math/Math.hpp"
#include "Render/Shader.hpp"
#include "Render/ShaderStorageBuffer.hpp"
#include "glad/glad.h"
#include "glfw3.h"

class Render
{
private:
    inline static GLFWwindow* window;

    struct RenderData
    {
        unsigned int MeshId;
        unsigned int MeshNumber;
        unsigned int Texture2DId;
        unsigned int ShaderId;
        unsigned int Amount = 0;
        std::vector<float> TransformDatas = std::vector<float>();

        bool operator<(const RenderData& other) const
        {
            if (MeshId != other.MeshId)
                return MeshId < other.MeshId;
    
            if (MeshNumber != other.MeshNumber)
                return MeshNumber < other.MeshNumber;

            if (Texture2DId != other.Texture2DId)
                return Texture2DId < other.Texture2DId;

            return ShaderId < other.ShaderId;
        }
    };

public:
    inline static void Start ()
    {
        if (!glfwInit())
            throw std::runtime_error("Start window fail");
        
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        window = glfwCreateWindow(
            Arcarna::Config::WindowWidth,
            Arcarna::Config::WindowHeight,
            Arcarna::Config::WindowName.c_str(),
            NULL,
            NULL
        );
        if (!window)
        {
            glfwTerminate();
            throw std::runtime_error("Start window fail");
        }

        glfwMakeContextCurrent(window);

        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
            throw std::runtime_error("Start window fail");

        ShaderStorageBuffer::CreateTransform();
    }

    inline static void Update ()
    {
        if (!glfwWindowShouldClose(window) && Arcarna::Config::IsRunning)
        {
            glClear(GL_COLOR_BUFFER_BIT);

            std::map<RenderData, int> IndexMap;
            std::vector<RenderData> RenderDatas;

            for (Entity& entity : Scene::World.View<Renderer>())
            {
                unsigned int EntityId = entity.GetId();
                if (Scene::World.HasComponent<Transform>(EntityId))
                {
                    unsigned int MeshId = Scene::World.GetComponent<Renderer>(EntityId).MeshId;
                    unsigned int MeshNumber = Scene::World.GetComponent<Renderer>(EntityId).MeshNumber;
                    unsigned int Texture2DId = Scene::World.GetComponent<Renderer>(EntityId).Texture2DId;

                    Transform& ModelTransform = Scene::World.GetComponent<Transform>(EntityId);
                    Transform& CameraTransform = Scene::World.GetComponent<Transform>(Scene::MainCameraEntityId);
                    Camera& CameraData = Scene::World.GetComponent<Camera>(Scene::MainCameraEntityId);
                    
                    RenderData renderData = {
                        MeshId,
                        MeshNumber,
                        Texture2DId,
                        BuiltinShader::DefaultId
                    };

                    auto it = IndexMap.find(renderData);
                    int Index = -1;
                    if (it == IndexMap.end())
                    {
                        RenderDatas.push_back(std::move(renderData));
                        Index = RenderDatas.size() - 1;
                        IndexMap[renderData] = Index;

                        RenderDatas[Index].TransformDatas.push_back(CameraTransform.GetPosition().x);
                        RenderDatas[Index].TransformDatas.push_back(CameraTransform.GetPosition().y);
                        RenderDatas[Index].TransformDatas.push_back(CameraTransform.GetPosition().z);
                        RenderDatas[Index].TransformDatas.push_back(CameraTransform.GetRotation().x);
                        RenderDatas[Index].TransformDatas.push_back(CameraTransform.GetRotation().y);
                        RenderDatas[Index].TransformDatas.push_back(CameraTransform.GetRotation().z);
                        RenderDatas[Index].TransformDatas.push_back(CameraData.WidthScale);
                        RenderDatas[Index].TransformDatas.push_back(Arcarna::Config::Aspect);
                    }
                    else
                    {
                        Index = it->second;
                    }
                    ++RenderDatas[Index].Amount;

                    RenderDatas[Index].TransformDatas.push_back(ModelTransform.GetPosition().x);
                    RenderDatas[Index].TransformDatas.push_back(ModelTransform.GetPosition().y);
                    RenderDatas[Index].TransformDatas.push_back(ModelTransform.GetPosition().z);
                    RenderDatas[Index].TransformDatas.push_back(ModelTransform.GetScale().x);
                    RenderDatas[Index].TransformDatas.push_back(ModelTransform.GetScale().y);
                    RenderDatas[Index].TransformDatas.push_back(ModelTransform.GetScale().z);
                    RenderDatas[Index].TransformDatas.push_back(ModelTransform.GetRotation().x);
                    RenderDatas[Index].TransformDatas.push_back(ModelTransform.GetRotation().y);
                    RenderDatas[Index].TransformDatas.push_back(ModelTransform.GetRotation().z);
                }
            }

            for (int i = 0; i < RenderDatas.size(); ++i)
            {
                unsigned int MeshId = RenderDatas[i].MeshId;
                unsigned int MeshNumber = RenderDatas[i].MeshNumber;
                unsigned int Texture2DId = RenderDatas[i].Texture2DId;
                unsigned int ShaderId = RenderDatas[i].ShaderId;
                unsigned int IndexBufferId = Mesh::GetIndexBufferId(MeshId);

                Mesh::Bind(MeshId);
                Texture2D::Bind(Texture2DId);
                Shader::Bind(ShaderId);

                ShaderStorageBuffer::Load(BuiltinSSBO::TransformId, RenderDatas[i].TransformDatas);
                ShaderStorageBuffer::Bind(BuiltinSSBO::TransformBinding);

                glDrawElementsInstanced(GL_TRIANGLES, IndexBuffer::Size(IndexBufferId), GL_UNSIGNED_INT, nullptr, RenderDatas[i].Amount);
            }

            glfwSwapBuffers(window);

            glfwPollEvents();
        }
        else
            End();
    }

    inline static void End ()
    {
        glfwTerminate();
        Arcarna::Config::IsRunning = false;
    }
};