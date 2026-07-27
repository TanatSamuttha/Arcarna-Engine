#pragma once

#include <stdexcept>

#include "Config/Config.hpp"
#include "Scene/Scene.hpp"
#include "Render/Renderer.hpp"
#include "Physics/Transform.hpp"
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
        if (!glfwWindowShouldClose(window))
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
                    unsigned int IndexBufferId = IndexBuffer::Size(Mesh::GetIndexBufferId(MeshId));
                    Mesh::Bind(MeshId);

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
    }
};