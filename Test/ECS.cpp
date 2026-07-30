#include <iostream>

#include "Assert.hpp"
#include "Scene/Scene.hpp"

class Position
{
public:
    int x = 0, y = 0;

    void IncreaseX ()
    {
        x++;
    }

    void IncreaseY ()
    {
        y++;
    }
};

class Color
{
public:
    int r;
    int g;
    int b;

    Color () : r(225), g(225), b(225) {}

    Color (int r, int g, int b) : r(r), g(g), b(b) {}

    void SetColor(int r, int g, int b)
    {
        this->r = r;
        this->g = g;
        this->b = b;
    }
};

int main ()
{
    Scene::SetNewScene();

    unsigned int slimeId = Scene::World.NewEntity();

    Scene::World.AddComponent<Color>(slimeId, 255, 43, 12);
    Scene::World.AddComponent<Position>(slimeId);
    Color& slimeColor = Scene::World.GetComponent<Color>(slimeId);
    Position& slimePos = Scene::World.GetComponent<Position>(slimeId);

    unsigned int orcId = Scene::World.NewEntity();

    Scene::World.AddComponent<Color>(orcId, 12, 255, 35);
    Scene::World.AddComponent<Position>(orcId);
    Position& orcPos = Scene::World.GetComponent<Position>(orcId);
    orcPos.x = 435;
    Color& orcColor = Scene::World.GetComponent<Color>(orcId);

    Assert(0, Scene::World.GetComponent<Position>(slimeId).x, "Slime position (Get component test)");
    Assert(435, orcPos.x, "Orc position");

    Scene::World.RemoveComponent<Color>(slimeId);

    Assert(255, Scene::World.GetComponent<Color>(orcId).g, "Orc color (Remove componet test)");

    unsigned int paladinId = Scene::World.NewEntity();
    Entity& paladin = Scene::World.GetEntity(paladinId);

    Scene::World.AddComponent<Position>(paladinId, 12, 13);

    unsigned int paladin2Id = Scene::World.NewEntity();
    Entity& paladin2 = Scene::World.GetEntity(paladin2Id);

    Scene::World.AddComponent<Position>(paladin2Id, 14, 15);

    Scene::World.DestroyEntity(orcId);

    Assert(14, Scene::World.GetComponent<Position>(paladin2Id).x, "Paladin2 position (Destroy entity test)");
    Assert(12, Scene::World.GetComponent<Position>(paladinId).x, "Paladin position");

    Assert(true, Scene::World.HasComponent<Position>(paladin2Id), "Paladin2 has position (Has component test)");
    Assert(false, Scene::World.HasComponent<Color>(paladin2Id), "Paladin2 has color");

    Scene::World.DestroyEntity(slimeId);
    Scene::World.DestroyEntity(paladinId);
    Scene::World.DestroyEntity(paladin2Id);

    unsigned int monster1Id = Scene::World.NewEntity<Color, Position>();
    unsigned int monster2Id = Scene::World.NewEntity<Color>();
    unsigned int monster3Id = Scene::World.NewEntity<Color, Position>();
    unsigned int monster4Id = Scene::World.NewEntity<Color, Position>();

    Assert(3u, monster1Id, "Destroy entity");

    bool IsNotCall = true;

    for(Entity& entity : Scene::World.View<Color, Position>())
    {
        if (entity.GetId() == 2)
            IsNotCall = false;
    }

    Assert(true, true, "View");

    return 0;
}