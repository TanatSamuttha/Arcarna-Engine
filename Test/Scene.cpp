#include "Assert.hpp"
#include "Engine/Scene/Scene.hpp"

int main ()
{
    unsigned int SceneId = Scene::NewScene();
    Scene::SetScene(SceneId);

    Assert(0u, SceneId, "First scene id");

    return 0;
}