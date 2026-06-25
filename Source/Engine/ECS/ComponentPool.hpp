#pragma once

#include <vector>
#include <unordered_map>

#include "Entity.hpp"

template<class T>
class ComponentPool : public IPool
{
private:
    std::vector<T> Components;
    std::vector<int> Entities;
    std::unordered_map<int, int> EntityToIdx;

public:
    void AddComponent (T NewComponent, int EntityId)
    {
        EntityToIdx[Components.size()] = EntityId;
        Components.push_back(NewComponent);
    }

    int GetIndex (int EntityId)
    {
        auto it = EntityToIdx.find(EntityId);

        if (it == EntityToIdx.end())
        {
            return -1;
        }

        return it->second;
    }
};
