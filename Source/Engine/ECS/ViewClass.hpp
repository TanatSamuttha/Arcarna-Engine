#pragma once

#include <vector>

#include "IPool.hpp"

class Scene;

template<class... Components>
class ViewClass
{
private:
    using iterator = std::vector<unsigned int>::iterator;

    iterator beginIt;
    iterator endIt;

public:
    ViewClass(iterator beginIt, iterator endIt) : beginIt(beginIt), endIt(endIt) {}

    class Iterator
    {
    private:
        iterator currentIt;
        iterator endIt;

    public:
        Iterator(iterator beginIt, iterator endIt) : currentIt(beginIt), endIt(endIt) {}

        Iterator& operator++()
        {
            currentIt++;
            while (currentIt != endIt && !(Scene::World.HasComponent<Components>(*currentIt) && ...))
                currentIt++;
            return *this;
        }

        bool operator!=(const Iterator& other) const
        {
            return currentIt != other.currentIt;
        }

        size_t operator*() const
        {
            return *currentIt;
        }
    };

    Iterator begin()
    {
        return Iterator(beginIt, endIt);
    }

    Iterator end()
    {
        return Iterator(endIt, endIt);
    }
};