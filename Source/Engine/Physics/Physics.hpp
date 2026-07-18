#pragma once

#include "Scene/Scene.hpp"
#include "Physics/RigidBody.hpp"
#include "Physics/Transform.hpp"
#include "Math/Math.hpp"

namespace Arcarna
{
    class Physics
    {
    private:
        inline static float dt;
    
    public:
        inline static float Gravity = -9.8;
        inline static const int ForceMode = 0;
        inline static const int ImpulseMode = 1;

        static void Start ();

        static void Update (const float dt);

        static float Getdt ();
    };
}