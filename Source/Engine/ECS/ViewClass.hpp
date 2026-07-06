#pragma once

#include <vector>

#include "IPool.hpp"

class Scene;
class Entity;

template<class... Components>
class ViewClass
{
private:
    using iterator = std::vector<unsigned int>::iterator;

    iterator beginIt;
    iterator endIt;

public:
    ViewClass (iterator beginIt, iterator endIt) : beginIt(beginIt), endIt(endIt) {}

    class Iterator
    {
    private:
        iterator currentIt;
        iterator endIt;

        void SearchNext ()
        {
            while (currentIt != endIt && !(Scene::World.HasComponent<Components>(*currentIt) && ...))
                currentIt++;
        }

    public:
        Iterator (iterator beginIt, iterator endIt) : currentIt(beginIt), endIt(endIt) 
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
            return Scene::World.GetEntity(*currentIt);
        }
    };

    Iterator begin ()
    {
        return Iterator(beginIt, endIt);
    }

    Iterator end ()
    {
        return Iterator(endIt, endIt);
    }
};