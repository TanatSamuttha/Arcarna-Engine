#include "Scene/Scene.hpp"
#include "Sprite/Sprite.hpp"
#include "Physics/Physics.hpp"
#include "Render/Renderer.hpp"

class AddBoxes
{
public:
    inline static int RectangleTId;

    inline static void Start ()
    {
        size_t n = 100000;
        for (int i = 0; i < n/2; ++i)
        {
            unsigned int RectangleEId = Scene::World.NewEntity<Transform, RigidBody>();
            Sprite Rectangle(RectangleTId);
            Scene::World.AddComponent<Renderer>(RectangleEId, Rectangle);
            Scene::World.GetComponent<Transform>(RectangleEId).SetPosition(Arcarna::Math::Vector3(-5, 0, 0));
            Scene::World.GetComponent<RigidBody>(RectangleEId).SetVelocity(Arcarna::Math::Vector3(6, 6, 0));
        }
        for (int i = 0; i < n/2; ++i)
        {
            unsigned int RectangleEId = Scene::World.NewEntity<Transform, RigidBody>();
            Sprite Rectangle(RectangleTId);
            Scene::World.AddComponent<Renderer>(RectangleEId, Rectangle);
            Scene::World.GetComponent<Transform>(RectangleEId).SetPosition(Arcarna::Math::Vector3(3, 5, 0));
        }
    }
};