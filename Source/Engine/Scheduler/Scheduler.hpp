#pragma once

#include "Scripts/Init.hpp"
#include "Physics/Physics.hpp"
#include "Render/Render.hpp"
#include "Mesh/Mesh.hpp"

class Scheduler
{
public:
    inline static void Start ()
    {
        Render::Start();
        Mesh::Start();
        Arcarna::Physics::Start();

        Arcarna::Init();
    }

    inline static void Update (double dt)
    {
        Arcarna::Physics::Update(dt);
        Render::Update();
    }
};