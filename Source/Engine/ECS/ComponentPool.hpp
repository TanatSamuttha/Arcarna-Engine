#pragma once

#include <vector>
#include <unordered_map>

#include "Entity.hpp"

template<class T>
class ComponentPool : public IPool
{
private:
    std::vector<T> Components;
    std::vector<unsigned> Entities;
    std::unordered_map<unsigned int, size_t> EntityToComponent;
    using iterator = std::unordered_map<unsigned int, size_t>::iterator;

public:
    void AddComponent (T NewComponent, unsigned int EntityId)
    {
        iterator ComponentIt = EntityToComponent.find(EntityId);
        if (ComponentIt != EntityToComponent.end())
            throw std::runtime_error("Component already exists");

        EntityToComponent.emplace(EntityId, Components.size());
        Components.emplace_back(NewComponent);
        Entities.emplace_back(EntityId);
    }

    int GetIndex (unsigned int EntityId)
    {
        iterator ComponentIt = EntityToComponent.find(EntityId);
        if (ComponentIt == EntityToComponent.end())
            throw std::runtime_error("Component not found");

        return ComponentIt->second;
    }

    T& GetComponent (unsigned int EntityId)
    {
        return Components[GetIndex(EntityId)];
    }

    void RemoveComponent (unsigned int EntityId)
    {
        iterator ComponentIt = EntityToComponent.find(EntityId);
        if (ComponentIt == EntityToComponent.end())
            throw std::runtime_error("Component not found");

        size_t removing = ComponentIt->second;
        size_t last = Components.size() - 1;

        if (removing != last)
        {
            Components[removing] = std::move(Components[last]);
            Entities[removing] = Entities[last];
            EntityToComponent[Entities[removing]] = removing;
        }

        Components.pop_back();
        Entities.pop_back();
        EntityToComponent.erase(EntityId);
    }
};
