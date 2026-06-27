#include <iostream>

#include "Assert.hpp"
#include "Engine/Scene/Scene.hpp"

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
    Entity& slime = Scene::World.GetEntity(slimeId);

    Scene::World.AddComponent<Color>(slime, 255, 43, 12);
    Scene::World.AddComponent<Position>(slime);
    Color& slimeColor = Scene::World.GetComponent<Color>(slime);
    Position& slimePos = Scene::World.GetComponent<Position>(slime);

    unsigned int orcId = Scene::World.NewEntity();
    Entity orc = Scene::World.GetEntity(orcId);

    Scene::World.AddComponent<Color>(orc, 12, 255, 35);
    Scene::World.AddComponent<Position>(orc);
    Position& orcPos = Scene::World.GetComponent<Position>(orc);
    orcPos.x = 435;
    Color& orcColor = Scene::World.GetComponent<Color>(orc);

    slimePos = Scene::World.GetComponent<Position>(slime);

    Assert(0, slimePos.x, "Slime position (Get component test)");
    Assert(435, orcPos.x, "Orc position");

    Scene::World.RemoveComponent<Color>(slime);

    orcColor = Scene::World.GetComponent<Color>(orc);
    Assert(255, orcColor.g, "Orc color (Remove componet test)");

    unsigned int paladinId = Scene::World.NewEntity();
    Entity paladin = Scene::World.GetEntity(paladinId);

    Scene::World.AddComponent<Position>(paladin, 12, 13);

    unsigned int paladin2Id = Scene::World.NewEntity();
    Entity paladin2 = Scene::World.GetEntity(paladin2Id);

    Scene::World.AddComponent<Position>(paladin2, 14, 15);

    Scene::World.DestroyEntity(orc);

    Assert(14, Scene::World.GetComponent<Position>(paladin2).x, "Paladin position2 (Destroy entity test)");
    Assert(12, Scene::World.GetComponent<Position>(paladin).x, "Paladin position");

    Assert(true, Scene::World.HasComponent<Position>(paladin2), "Paladin has position (Has component test)");
    Assert(false, Scene::World.HasComponent<Color>(paladin2), "Paladin has color");

    return 0;
}