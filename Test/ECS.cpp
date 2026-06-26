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
    Color color(255, 43, 12);
    World::AddComponent<Color>(slime, color);
    World::AddComponent<Position>(slime);
    Position& slimePos = World::GetComponent<Position>(slime);
    Color& slimeColor = World::GetComponent<Color>(slime);


    Entity orc = World::NewEntity();
    color.SetColor(12, 255, 35);
    World::AddComponent<Color>(orc, color);
    World::AddComponent<Position>(orc);
    Position& orcPos = World::GetComponent<Position>(orc);
    orcPos.x = 435;
    Color& orcColor = World::GetComponent<Color>(orc);

    Assert(0, slimePos.x);
    Assert(435, orcPos.x);

    World::RemoveComponent<Color>(slime);

    orcColor = World::GetComponent<Color>(orc);
    Assert(255, orcColor.g);

    return 0;
}