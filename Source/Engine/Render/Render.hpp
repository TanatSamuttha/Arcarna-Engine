#pragma once

#include <stdexcept>

#include "Config/Config.hpp"
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