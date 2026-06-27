#include "Assert.hpp"
#include "Engine/Scene/Scene.hpp"

class Dummy
{
public:
    int value;

    Dummy (int value) : value(value) {}
};

int main ()
{
    unsigned int SceneId = Scene::NewScene();
    Scene::SetScene(SceneId);

    Assert(0u, SceneId, "First scene id");

    Entity& dummy = Scene::World.NewEntity();
    Scene::World.AddComponent<Dummy>(dummy, 23);

    Scene::SetNewScene();


    return 0;
}