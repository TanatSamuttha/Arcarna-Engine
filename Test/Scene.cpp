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

    unsigned int dummyId = Scene::World.NewEntity();
    Entity& dummy = Scene::World.GetEntity(dummyId);
    Scene::World.AddComponent<Dummy>(dummy, 1);

    unsigned int Scene2Id = Scene::SetNewScene();

    unsigned int dummy2Id = Scene::World.NewEntity();
    Entity& dummy2 = Scene::World.GetEntity(dummy2Id);
    Scene::World.AddComponent<Dummy>(dummy2, 2);

    Assert(dummyId, dummy2Id, "First entity in different scene");

    Scene::SetScene(Scene2Id);
    Entity& dummy1 = Scene::World.GetEntity(dummyId);

    Assert(1, Scene::World.GetComponent<Dummy>(dummy1).value);

    return 0;
}