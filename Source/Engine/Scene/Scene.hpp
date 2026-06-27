#include <vector>

#include "ECS/World.hpp"

class Scene
{
public:
    inline static World World;

    inline static std::vector<unsigned int> FreeIds;

    inline static std::vector<Scene> Scenes;

    int Id;

    Scene (int Id) : Id(Id) {}

    unsigned int NewScene ()
    {
        unsigned int NewId = Scenes.size();

        if (!FreeIds.empty())
        {
            NewId = FreeIds.back();
            FreeIds.pop_back();
        }

        if (NewId >= Scenes.size())
        {
            Scenes.resize(NewId + 1);
        }

        Scenes.emplace_back(1);

        return NewId;
    }
};