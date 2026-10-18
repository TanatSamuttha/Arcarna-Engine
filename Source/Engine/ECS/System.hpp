#pragma once

#include "Scripts/Init.hpp"
#include "Physics/Physics.hpp"
#include "Render/Render.hpp"
#include "Mesh/Mesh.hpp"

#include <functional>
#include <string>
#include <vector>

class System
{
private:
    inline static std::vector<std::function<void()>> Task;
    inline static std::vector<std::string> TaskName;

public:
    inline static void AddUpdate (std::function<void()> Callable)
    {
        Task.push_back(Callable);
    }

    inline static void AddUpdate (std::function<void()> Callable, std::string DebugName)
    {
        Task.push_back(Callable);
        TaskName.push_back(DebugName);
    }

    inline static void PrintUpdate ()
    {
        std::cout << "Assigned update:\n";
        for (std::string& Name : TaskName)
        {
            std::cout << Name << '\n';
        }
        std::cout << "===============\n";
    }

    inline static void Start ()
    {
        Task.reserve(2);
        Arcarna::Physics::Start();
        AddUpdate(Arcarna::Physics::Update, "Physics");

        Render::Start();
        Mesh::Start();

        Arcarna::Init();

        AddUpdate(Render::Update, "Render");
    }

    inline static void Update (double dt)
    {
        Arcarna::Physics::dt = dt;
        for (std::function<void()>& t : Task)
        {
            t();
        }
    }
};