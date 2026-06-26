#include <iostream>

#include "Assert.hpp"
#include "Engine/ECS/World.hpp"

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
    Entity slime = World::NewEntity();
    World::AddComponent<Color>(slime, 255, 43, 12);
    World::AddComponent<Position>(slime);
    Color& slimeColor = World::GetComponent<Color>(slime);
    Position& slimePos = World::GetComponent<Position>(slime);

    Entity orc = World::NewEntity();
    World::AddComponent<Color>(orc, 12, 255, 35);
    World::AddComponent<Position>(orc);
    Position& orcPos = World::GetComponent<Position>(orc);
    orcPos.x = 435;
    Color& orcColor = World::GetComponent<Color>(orc);

    slimePos = World::GetComponent<Position>(slime);

    Assert(0, slimePos.x);
    Assert(435, orcPos.x);

    World::RemoveComponent<Color>(slime);

    orcColor = World::GetComponent<Color>(orc);
    Assert(255, orcColor.g);

    return 0;
}