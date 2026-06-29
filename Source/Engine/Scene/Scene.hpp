#include <vector>

#include "ECS/World.hpp"

class Scene
{
public:

    inline static std::vector<unsigned int> FreeIds;

    inline static std::vector<Scene> Scenes;

    unsigned int Id;

    World ThisWorld;

    inline static World World;
    inline static unsigned int CurrentId;

    Scene () : Id(0) {}

    Scene (int Id) : Id(Id) {}

    inline static unsigned int NewScene ()
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

        return NewId;
    }

    inline static void SetScene (unsigned int Id)
    {
        if (CurrentId == Id) 
            return;

        Scenes[CurrentId].ThisWorld = std::move(World);
        World = std::move(Scenes[Id].ThisWorld);
        CurrentId = Id;
    }

    inline static unsigned int SetNewScene ()
    {
        unsigned int Id = NewScene();
        SetScene(Id);
        return Id;
    }

    inline static unsigned int GetScene ()
    {
        return CurrentId;
    }

    inline static void RemoveScene (unsigned int Id)
    {
        if (Id == CurrentId)
            throw std::runtime_error("Remove current scene");

        FreeIds.push_back(Id);
        Scenes[Id] = std::move(Scene());
    }
};