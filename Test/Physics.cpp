#include "Assert.hpp"
#include "Scene/Scene.hpp"
#include "Physics/Physics.hpp"

int main ()
{
    Scene::SetNewScene();

    unsigned int BodyId = Scene::World.NewEntity<Transform, RigidBody>();

    

    return 0;
}