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
        inline static float Gravity = -9.8;
        inline static float dt;

    public:
        inline static const int ForceMode = 0;
        inline static const int ImpulseMode = 1;

        static void Start ()
        {
            Gravity = -9.8;
        }

        static void Update (const float dt)
        {
            Physics::dt = dt;

            for (Entity& entity : Scene::World.View<RigidBody>())
            {
                unsigned int EntityId = entity.GetId();

                RigidBody& rigidBody = Scene::World.GetComponent<RigidBody>(EntityId);
                
                rigidBody.AddForce(Arcarna::Math::Vector2(0, Gravity), ForceMode);

                if (Scene::World.HasComponent<Transform>(EntityId))
                {
                    Transform& transform = Scene::World.GetComponent<Transform>(EntityId);

                    transform.SetPosition(
                        transform.GetPosition() +
                        rigidBody.GetVelocity() * dt +  rigidBody.GetForce() * 0.5f * dt * dt
                    );
                }

                rigidBody.SetVelocity(rigidBody.GetVelocity() + rigidBody.GetForce() * dt);
                rigidBody.ResetForce();
            }
        }

        static float Getdt ()
        {
            return dt;
        }

        static void SetGravity (const float Gravity)
        {
            Physics::Gravity = Gravity;
        }
    };
}