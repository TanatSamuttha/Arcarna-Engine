#pragma once

#include <vector>
#include <unordered_map>

#include "Entity.hpp"

template<class T>
class ComponentPool : public IPool
{
private:
    std::vector<T> Components;
    std::vector<unsigned int> DenseEntities;
    std::unordered_map<unsigned int, size_t> EntityToIdx;
    std::unordered_map<unsigned int, size_t> EntityIdToDense;

public:
    void AddComponent (T NewComponent, unsigned int EntityId)
    {
        if (EntityToIdx.contains(EntityId))
            throw std::runtime_error("Component already exists");

        EntityToIdx[EntityId] = Components.size();
        Components.push_back(NewComponent);

        EntityIdToDense[EntityId] = DenseEntities.size();
        DenseEntities.push_back(EntityId);
    }

    int GetIndex (unsigned int EntityId)
    {
        if (!EntityToIdx.contains(EntityId))
            throw std::runtime_error("Component not found");

        return EntityToIdx[EntityId];
    }

    T& GetComponent (unsigned int EntityId)
    {
        if (!EntityToIdx.contains(EntityId))
            throw std::runtime_error("Component not found");

        return Components[EntityToIdx[EntityId]];
    }

    void RemoveComponent (unsigned int EntityId)
    {
        Components[EntityToIdx[EntityId]] = *(Components.end() - 1);
        Components.pop_back();

        DenseEntities[EntityIdToDense[EntityId]] = *(DenseEntities.end() - 1);
        DenseEntities.pop_back();
    }
};
