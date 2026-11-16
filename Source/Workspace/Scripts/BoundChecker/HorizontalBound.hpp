#include "Physics/Physics.hpp"
#include "Scene/Scene.hpp"
#include "Scripts/BoundChecker/Added.hpp"

class Horizontalbound
{
public:
    inline static void Update ()
    {
        for (Entity& entity : Scene::World.View<Transform, RigidBody, Added>())
        {
            Transform& transform = Scene::World.GetComponent<Transform>(entity.GetId());
            RigidBody& rigidBody = Scene::World.GetComponent<RigidBody>(entity.GetId());
            Added& added = Scene::World.GetComponent<Added>(entity.GetId());
            if (transform.GetPosition().x <= -5 && !added.Hori)
            {
                rigidBody.SetVelocity(Arcarna::Math::Vector3(
                    6,
                    rigidBody.GetVelocity().y,
                    rigidBody.GetVelocity().z
                ));
                added.Hori = true;
            }
            else if (transform.GetPosition().x >= 5 && !added.Hori)
            {
                rigidBody.SetVelocity(Arcarna::Math::Vector3(
                    -6,
                    rigidBody.GetVelocity().y,
                    rigidBody.GetVelocity().z
                ));
                added.Hori = true;
            }
            else if (transform.GetPosition().x > -5 && transform.GetPosition().x < 5)
            {
                added.Hori = false;
            }
        }
    }
};