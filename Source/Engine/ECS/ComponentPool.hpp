#pragma once

#include <vector>
#include <unordered_map>

#include "Entity.hpp"

template<class T>
class ComponentPool : public IPool
{
private:
    std::vector<T> Components;
    std::unordered_map<unsigned int, size_t> EntityToComponent;
    std::unordered_map<unsigned int, size_t> EntityIdToDense;
    std::unordered_map<size_t, size_t> ComponentToEntity;

public:
    void AddComponent (T NewComponent, unsigned int EntityId)
    {
        if (EntityToComponent.contains(EntityId))
            throw std::runtime_error("Component already exists");

        EntityToComponent[EntityId] = Components.size();
        ComponentToEntity[Components.size()] = Components.size();
        Components.push_back(NewComponent);
    }

    int GetIndex (unsigned int EntityId)
    {
        if (!EntityToComponent.contains(EntityId))
            throw std::runtime_error("Component not found");

        return EntityToComponent[EntityId];
    }

    T& GetComponent (unsigned int EntityId)
    {
        if (!EntityToComponent.contains(EntityId))
            throw std::runtime_error("Component not found");

        return Components[EntityToComponent[EntityId]];
    }

    void RemoveComponent (unsigned int EntityId)
    {
        size_t RemovingComIdx = EntityToComponent[EntityId];
        size_t ReplacingComIdx = Components.size() - 1;

        size_t ReplacingEnId = ComponentToEntity[ReplacingComIdx];

        Components[RemovingComIdx] = Components[ReplacingComIdx];
        EntityToComponent[ReplacingEnId] = RemovingComIdx;
        Components.pop_back();
    }
};
