#pragma once

#include <vector>

#include "IPool.hpp"

class World;
class Entity;

template<class... Components>
class ViewClass
{
private:
    using iterator = std::vector<unsigned int>::iterator;

    World& world;

    iterator beginIt;
    iterator endIt;

public:
    ViewClass (iterator beginIt, iterator endIt, World& world) : beginIt(beginIt), endIt(endIt), world(world) {}

    class Iterator
    {
    private:
        World& world;

        iterator currentIt;
        iterator endIt;

        void SearchNext ()
        {
            while (currentIt != endIt && !(world.template HasComponent<Components>(*currentIt) && ...))
                currentIt++;
        }

    public:
        Iterator (iterator beginIt, iterator endIt, World& world) : currentIt(beginIt), endIt(endIt), world(world)
        {
            SearchNext();
        }

        Iterator& operator++ ()
        {
            currentIt++;
            SearchNext();
            return *this;
        }

        bool operator!= (const Iterator& other) const
        {
            return currentIt != other.currentIt;
        }

        Entity& operator* () const
        {
            return world.GetEntity(*currentIt);
        }
    };

    Iterator begin ()
    {
        return Iterator(beginIt, endIt, world);
    }

    Iterator end ()
    {
        return Iterator(endIt, endIt, world);
    }
};