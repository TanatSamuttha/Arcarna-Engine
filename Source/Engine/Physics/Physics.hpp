#pragma once

#include "Scene/Scene.hpp"
#include "Physics/RigidBody.hpp"
#include "Physics/Transform.hpp"
#include "Math/Math.hpp"

class System;

namespace Arcarna
{
    class Physics
    {
    private:
        inline static float dt;
        friend class ::System;
    
    public:
        bool Active = true;
        inline static float Gravity = -9.8;

        static void Start ();

        static void Update ();

        static float Getdt ();
    };
}