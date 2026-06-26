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

int main ()
{
    Entity slime = World::NewEntity();
    World::AddComponent<Position>(slime);

    Position pos = World::GetComponent<Position>(slime);

    Assert(0, pos.x);

    return 0;
}