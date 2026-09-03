#pragma once

#include <stdexcept>

#include "Config.hpp"
#include "Camera/Camera.hpp"
#include "Scene/Scene.hpp"
#include "Render/Renderer.hpp"
#include "Physics/Transform.hpp"
#include "Math/Math.hpp"
#include "Render/Shader.hpp"
#include "glad/glad.h"
#include "glfw3.h"

class Render
{
private:
    inline static GLFWwindow* window;

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
    }

    inline static void Update ()
    {
        if (!glfwWindowShouldClose(window) && Arcarna::Config::IsRunning)
        {
            glClear(GL_COLOR_BUFFER_BIT);

            for (Entity& entity : Scene::World.View<Renderer>())
            {
                unsigned int EntityId = entity.GetId();
                if (Scene::World.HasComponent<Transform>(EntityId))
                {
                    unsigned int MeshId = Scene::World.GetComponent<Renderer>(EntityId).MeshId;
                    unsigned int MeshNumber = Scene::World.GetComponent<Renderer>(EntityId).MeshNumber;
                    unsigned int Texture2DId = Scene::World.GetComponent<Renderer>(EntityId).Texture2DId;
                    unsigned int IndexBufferId = Mesh::GetIndexBufferId(MeshId);
                    Mesh::Bind(MeshId);
                    Texture2D::Bind(Texture2DId);

                    Transform& transform = Scene::World.GetComponent<Transform>(EntityId);
                    Arcarna::Math::Matrix4 MVP = Arcarna::Math::Matrix4::MVP(
                        transform.GetPosition(), 
                        transform.GetScale(), 
                        Arcarna::Config::Aspect, 
                        Arcarna::Math::Vector2(0, 0),
                        Camera::Scale
                    );

                    Shader::SetMVP(BuiltinShader::DefaultId, MVP);

                    glDrawElements(GL_TRIANGLES, IndexBuffer::Size(IndexBufferId), GL_UNSIGNED_INT, nullptr);
                }
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