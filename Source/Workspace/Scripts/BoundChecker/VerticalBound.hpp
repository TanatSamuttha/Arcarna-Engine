#include "Physics/Physics.hpp"
#include "Scene/Scene.hpp"

class Verticalbound
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
            if (transform.GetPosition().y <= -5 && !Added)
            {
                rigidBody.AddForce(Arcarna::Math::Vector3(
                    0,
                    6,
                    0
                ), ForceMode::Impulse);
                Added = true;
            }
            else if (transform.GetPosition().y > -5)
            {
                Added = false;
            }
        }
    }
};