#include "Physics/Physics.hpp"
#include "Scene/Scene.hpp"
#include "Scripts/BoundChecker/Added.hpp"

class Verticalbound
{
public:
    inline static void Update ()
    {
        for (Entity& entity : Scene::World.View<Transform, RigidBody, Added>())
        {
            Transform& transform = Scene::World.GetComponent<Transform>(entity.GetId());
            RigidBody& rigidBody = Scene::World.GetComponent<RigidBody>(entity.GetId());
            Added& added = Scene::World.GetComponent<Added>(entity.GetId());
            if (transform.GetPosition().y <= -5 && !added.Verti)
            {
                rigidBody.SetVelocity(Arcarna::Math::Vector3(
                    rigidBody.GetVelocity().x,
                    10,
                    rigidBody.GetVelocity().z
                ));
                added.Verti = true;
            }
            else if (transform.GetPosition().y > -5)
            {
                added.Verti = false;
            }
        }
    }
};