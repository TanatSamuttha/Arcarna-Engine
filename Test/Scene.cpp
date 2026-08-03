#include "Assert.hpp"
#include "Scene/Scene.hpp"

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
    Scene::World.AddComponent<Dummy>(dummyId, 1);

    unsigned int Scene2Id = Scene::SetNewScene();

    Assert(1u, Scene2Id, "Second scene id");
    Assert(1u, Scene2Id, "Current scene id");

    unsigned int dummy2Id = Scene::World.NewEntity();
    Scene::World.AddComponent<Dummy>(dummy2Id, 2);

    Assert(dummyId, dummy2Id, "First entity in different scene");

    Scene::SetScene(SceneId);

    Assert(1, Scene::World.GetComponent<Dummy>(dummyId).value, "Recall entity in old scene");

    return 0;
}