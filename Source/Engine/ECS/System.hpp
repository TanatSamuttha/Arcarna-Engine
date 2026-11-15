#pragma once

#include "Scripts/Init.hpp"
#include "Physics/Physics.hpp"
#include "Render/Render.hpp"
#include "Mesh/Mesh.hpp"
#include "ariadne.hpp"

#include <functional>
#include <set>
#include <string>
#include <vector>

class EntryPoint;

class System
{
protected:
    friend class EntryPoint;
    inline static Ariadne::Graph<Ariadne::NoState> StartGraph;
    inline static Ariadne::Graph<Ariadne::NoState> UpdateGraph;
    inline static std::set<std::string> StartNoEndPoint;
    inline static std::vector<std::pair<std::string, std::string>> StartEdges;
    inline static std::set<std::string> UpdateNoEndPoint;
    inline static std::vector<std::pair<std::string, std::string>> UpdateEdges;

public:
    inline static std::string START_NODE = StartGraph.START;
    inline static std::string PHYSICS_NODE = "Physics";

    inline static void AddStart (std::function<void()> Callable, std::string TaskName, std::vector<std::string> Dependencies)
    {
        std::function callable = [Callable = std::move(Callable)](std::shared_ptr<Ariadne::NoState>)->std::string
        {
            Callable();
            return "";
        };

        StartGraph.addNode(TaskName, callable);

        for (std::string& Dependency : Dependencies)
        {
            StartEdges.push_back(std::pair(Dependency, TaskName));
            StartNoEndPoint.erase(Dependency);
            
        }

        StartNoEndPoint.insert(TaskName);
    }

    inline static void AddUpdate (std::function<void()> Callable, std::string TaskName, std::vector<std::string> Dependencies)
    {
        std::function callable = [Callable = std::move(Callable)](std::shared_ptr<Ariadne::NoState>)->std::string
        {
            Callable();
            return "";
        };

        UpdateGraph.addNode(TaskName, callable);

        for (std::string& Dependency : Dependencies)
        {
            UpdateEdges.push_back(std::pair(Dependency, TaskName));
            UpdateNoEndPoint.erase(Dependency);
        }

        UpdateNoEndPoint.insert(TaskName);
    }

    inline static void PrintUpdate ()
    {
        std::cout << "Assigned update:\n";
        UpdateGraph.print();
        std::cout << "===============\n";
    }

    inline static void Start ()
    {
        Arcarna::Physics::Start();
        AddUpdate(Arcarna::Physics::Update, PHYSICS_NODE, {UpdateGraph.START});
        Render::Start();
        Mesh::Start();
        Arcarna::Init();

        for (auto Edge : StartEdges)
        {
            StartGraph.addEdge(Edge.first, Edge.second);
        }
        StartEdges.clear();
        for (std::string TaskName : StartNoEndPoint)
        {
            StartGraph.addEdge(TaskName, StartGraph.END);
        }
        
        StartGraph.spawnWorker(5);
        // StartGraph.exec(); // Is bugging with Ariadne

        StartNoEndPoint.clear();
        std::vector<std::string> Dependencies;
        for (std::string TaskName : UpdateNoEndPoint)
        {
            Dependencies.push_back(TaskName);
        }
        UpdateNoEndPoint.clear();
        AddUpdate(Render::Update, "Render", Dependencies);
        for (auto Edge : UpdateEdges)
        {
            UpdateGraph.addEdge(Edge.first, Edge.second);
        }
        UpdateEdges.clear();
        UpdateGraph.addEdge("Render", UpdateGraph.END);

        StartGraph.wait();
        StartGraph.destroyWorker();
    }

    inline static void Update (double dt)
    {
        Arcarna::Physics::dt = dt;
        UpdateGraph.exec();
        UpdateGraph.wait();
    }
};