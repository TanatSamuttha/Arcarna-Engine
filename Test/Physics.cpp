#include <format>

#include "Assert.hpp"
#include "Scene/Scene.hpp"
#include "Physics/Physics.hpp"

void InitialSpeedProjectile (unsigned int BodyId, float ux, float uy, float x1, float y1, float x2, float y2, float dt)
{
    Scene::World.GetComponent<Transform>(BodyId).SetPosition(Arcarna::Math::Vector2(x1, y1));
    Scene::World.GetComponent<RigidBody>(BodyId).SetVelocity(Arcarna::Math::Vector2(ux, uy));

    Arcarna::Physics::Update(dt);

    Arcarna::Math::Vector2 PositionDiff = Scene::World.GetComponent<Transform>(BodyId).GetPosition() - Arcarna::Math::Vector2(x2, y2);

    Assert(
        true,
        PositionDiff.x < 1e-6 && PositionDiff.y < 1e-6,
        std::format("Initial speed <{}, {}> Answer <{}, {}> == <{}, {}>", ux, uy, x2, y2, Scene::World.GetComponent<Transform>(BodyId).GetPosition().x, Scene::World.GetComponent<Transform>(BodyId).GetPosition().y)
    );
}

int main ()
{
    Scene::SetNewScene();

    unsigned int BodyId = Scene::World.NewEntity<Transform, RigidBody>();

    Arcarna::Physics::Start();

    InitialSpeedProjectile(BodyId, 6, 5, 0, 0, 6, 0.1, 1);
    InitialSpeedProjectile(BodyId, 10, 25, 5, 10, 25, 40.4, 2);
    InitialSpeedProjectile(BodyId, 3, 12, -2, 4, 7, -4.1, 3);
    InitialSpeedProjectile(BodyId, 6, 18, 12, -5, 18, 8.1, 1);

    return 0;
}