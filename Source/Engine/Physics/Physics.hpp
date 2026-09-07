#pragma once

#include "Scene/Scene.hpp"
#include "Physics/RigidBody.hpp"
#include "Physics/Transform.hpp"
#include "Math/Math.hpp"

class Scheduler;

namespace Arcarna
{
    class Physics
    {
    private:
        inline static float dt;
        friend class ::Scheduler;
    
    public:
        inline static float Gravity = -9.8;

        static void Start ();

        static void Update ();

        static float Getdt ();
    };
}