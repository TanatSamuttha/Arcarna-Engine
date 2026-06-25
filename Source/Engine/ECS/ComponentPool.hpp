#pragma once

#include <vector>
#include <unordered_map>

#include "Entity.hpp"

template<class T>
class ComponentPool : public IPool
{
private:
    std::vector<T> Components;
    std::vector<unsigned int> Entities;
    std::unordered_map<unsigned int, size_t> EntityToIdx;

public:
    void AddComponent (T NewComponent, unsigned int EntityId)
    {
        if (EntityToIdx.contains(EntityId))
            throw std::runtime_error("Component already exists");

        EntityToIdx[EntityId] = Components.size();
        Components.push_back(NewComponent);
        Entities.push_back(EntityId);
    }

    int GetIndex (unsigned int EntityId)
    {
        if (!EntityToIdx.contains(EntityId))
            throw std::runtime_error("Component not found");

        return it->second;
    }

    T& GetComponent(unsigned int EntityId)
    {
        if (!EntityToIdx.contains(EntityId))
            throw std::runtime_error("Component not found");

        return Components[EntityToIdx[EntityId]];
    }
};
