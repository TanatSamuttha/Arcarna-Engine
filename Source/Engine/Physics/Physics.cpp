#include "Physics/Physics.hpp"

namespace Arcarna
{
    void Physics::Start ()
    {
        Gravity = -9.8;
    }

    void Physics::Update ()
    {
        for (Entity& entity : Scene::World.View<RigidBody>())
        {
            unsigned int EntityId = entity.GetId();

            if (!Scene::World.GetEntity(EntityId).Active)
                continue;

            RigidBody& rigidBody = Scene::World.GetComponent<RigidBody>(EntityId);

            if (!rigidBody.Active)
                continue;
        
            rigidBody.AddForce(Arcarna::Math::Vector3(0, Gravity, 0), ForceMode::Force);

            if (Scene::World.HasComponent<Transform>(EntityId))
            {
                Transform& transform = Scene::World.GetComponent<Transform>(EntityId);

                if (!transform.Active)
                    continue;

                transform.SetPosition(
                    transform.GetPosition() +
                    rigidBody.GetVelocity() * dt + rigidBody.GetForce() / rigidBody.GetMass() * 0.5f * dt * dt
                );
            }

            rigidBody.SetVelocity(rigidBody.GetVelocity() + rigidBody.GetForce() / rigidBody.GetMass() * dt);
            rigidBody.ResetForce();
        }
    }

    float Physics::Getdt ()
    {
        return dt;
    }
}