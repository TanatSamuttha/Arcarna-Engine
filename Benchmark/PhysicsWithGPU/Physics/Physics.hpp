#pragma once

#include "Scene/Scene.hpp"
#include "PhysicsWithGPU/Physics/RigidBody.hpp"
#include "PhysicsWithGPU/Physics/Transform.hpp"
#include "Math/Math.hpp"

class System;

namespace Arcarna
{
    class Physics
    {
    public:
        inline static float dt;
        friend class ::System;
    
        bool Active = true;
        inline static float Gravity = -9.8;

        static void Start ();

        static void Update ();

        static float Getdt ();
    };
}