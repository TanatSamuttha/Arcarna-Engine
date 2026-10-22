#include <chrono>
#include <iostream>
#include "Scene/Scene.hpp"
#include "PhysicsWithGPU/Physics/Physics.hpp"
#include "cpu.hpp"
#include "gpu.hpp"

int main ()
{
    size_t N = (size_t)1e7;

    // Initialize scene
    Scene::SetNewScene();

    // Initialize entities
    for (size_t i = 0; i < N; ++i)
    {
        Scene::World.NewEntity<RigidBody, Transform>();
    }

    std::cout << "Initialize done" << std::endl;

    auto start = std::chrono::steady_clock::now();
    CPU::Update();
    auto end = std::chrono::steady_clock::now();
    std::cout << "Physics system usage time" << std::endl;
    std::cout << "CPU: " << std::chrono::duration<double>(end - start).count() << std::endl;

    start = std::chrono::steady_clock::now();
    GPU::Update();
    end = std::chrono::steady_clock::now();
    std::cout << "GPU: " << std::chrono::duration<double>(end - start).count() << std::endl;

    return 0;
}

/*
nvcc Benchmark/PhysicsWithGPU/main.cpp Benchmark/PhysicsWithGPU/gpu.cu -o Build/Benchmark -O3 -ISource/Engine -ISource/Config -IBenchmark
*/