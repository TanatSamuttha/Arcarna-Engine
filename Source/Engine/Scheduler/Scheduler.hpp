#pragma once

#include "Scripts/Init.hpp"
#include "Physics/Physics.hpp"
#include "Render/Render.hpp"
#include "Mesh/Mesh.hpp"
#include "ariadne.hpp"

#include <cstddef>
#include <functional>
#include <utility>
#include <memory>
#include <string>

class Scheduler
{
private:
    inline static Ariadne::Graph<Ariadne::NoState> Graph;

public:
    inline static size_t Worker = 1;

    inline static void AddTask (std::string TaskName, std::function<void()> Callable)
    {
        std::function<std::string(std::shared_ptr<Ariadne::NoState>)> Wraper = 
        [Callable = std::move(Callable)](std::shared_ptr<Ariadne::NoState>) -> std::string
        {
            Callable();
            return "";
        };

        Graph.addNode(TaskName, Wraper);
    }

    inline static void AddDependency (std::string Task, std::string Dependency)
    {
        Graph.addEdge(Dependency, Task);
    }

    inline static void Start ()
    {
        Render::Start();
        AddTask("Render", Render::Update);

        Mesh::Start();

        Arcarna::Physics::Start();
        AddTask("Physics", Arcarna::Physics::Update);
        
        Arcarna::Init();

        AddDependency("Physics", Graph.START);
        AddDependency("Render", "Physics");
        AddDependency(Graph.END, "Render");
        Graph.spawnWorker(Worker);
    }

    inline static void Update (double dt)
    {
        Arcarna::Physics::dt = dt;
        Graph.exec();
        Graph.wait();
    }

    inline static void End ()
    {
        Graph.destroyWorker();
    }
};