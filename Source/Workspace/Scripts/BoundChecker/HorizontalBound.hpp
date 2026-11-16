#include "Physics/Physics.hpp"
#include "Scene/Scene.hpp"

class Horizontalbound
{
private:
    inline static bool Added = false;
public:
    inline static void Update ()
    {
        for (Entity& entity : Scene::World.View<Transform, RigidBody>())
        {
            Transform& transform = Scene::World.GetComponent<Transform>(entity.GetId());
            RigidBody& rigidBody = Scene::World.GetComponent<RigidBody>(entity.GetId());
            if (transform.GetPosition().x <= -5 && !Added)
            {
                rigidBody.SetVelocity(Arcarna::Math::Vector3(
                    6,
                    rigidBody.GetVelocity().y,
                    rigidBody.GetVelocity().z
                ));
                Added = true;
            }
            else if (transform.GetPosition().x >= 5 && !Added)
            {
                rigidBody.SetVelocity(Arcarna::Math::Vector3(
                    -6,
                    rigidBody.GetVelocity().y,
                    rigidBody.GetVelocity().z
                ));
                Added = true;
            }
            else if (transform.GetPosition().x > -5 && transform.GetPosition().x < 5)
            {
                Added = false;
            }
        }
    }
};