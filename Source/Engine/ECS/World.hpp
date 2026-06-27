#pragma once

#include <unordered_map>
#include <vector>
#include <queue>
#include <bitset>
#include <typeindex>
#include <memory>

#include "IPool.hpp"
#include "ComponentPool.hpp"
#include "Entity.hpp"

class World
{
private:
    inline static const unsigned int MAX_COMPONENT = 128;

    unsigned int NextComponentId = 0;

    std::vector<unsigned int> FreeIds;

    std::vector<std::unique_ptr<Entity>> Entities;
    std::vector<std::bitset<MAX_COMPONENT>> ComponentInEntity;
    std::vector<std::unique_ptr<IPool>> ComponentPools;

    template<class T>
    unsigned int GetComponentID ()
    {
        static unsigned int id = NextComponentId++;
        return id;
    }

    template<class T>
    ComponentPool<T>& GetPool ()
    {
        unsigned int ComponentId = GetComponentID<T>();

        if (ComponentId == ComponentPools.size())
            ComponentPools.push_back(std::make_unique<ComponentPool<T>>());

        return *static_cast<ComponentPool<T>*>(ComponentPools[ComponentId].get());
    }

public:
    Entity& NewEntity ()
    {
        auto entity_ptr = std::make_unique<Entity>();

        Entity& entity = *entity_ptr;

        unsigned int EntityId = Entities.size();
        if (!FreeIds.empty())
        {
            EntityId = FreeIds.back();
            FreeIds.pop_back();
        }

        if (EntityId >= Entities.size())
        {    
            Entities.resize(EntityId + 1);
            ComponentInEntity.resize(EntityId + 1);
        }
        entity.SetId(EntityId);
        Entities[EntityId] = std::move(entity_ptr);
        ComponentInEntity[EntityId] = 0;

        return entity;
    }

    void DestroyEntity (Entity& entity)
    {
        unsigned int EntityId = entity.GetId();
        std::bitset<MAX_COMPONENT>& mask = ComponentInEntity[EntityId];

        for (int i = 0; i < ComponentPools.size(); ++i)
        {
            if (mask.test(i))
            {
                ComponentPools[i]->RemoveComponent(EntityId);
            }
        }

        mask.reset();
        Entities[EntityId].reset();
        FreeIds.push_back(EntityId);
    }

    template<class T, class... Args>
    void AddComponent (const Entity& entity, Args&&... args)
    {   
        ComponentPool<T>& pool = GetPool<T>();
        
        unsigned int EntityId = entity.GetId();

        ComponentInEntity[EntityId].set(GetComponentID<T>());
        pool.AddComponent(EntityId, std::forward<Args>(args)...);
    }

    template<class T>
    T& GetComponent (const Entity& entity)
    {
        unsigned int ComponentId = GetComponentID<T>();
        
        ComponentPool<T>& pool = GetPool<T>();

        return pool.GetComponent(entity.GetId());
    }

    template<class T>
    bool HasComponent (const Entity& entity)
    {
        unsigned int ComponentId = GetComponentID<T>();

        return ComponentInEntity[entity.GetId()].test(ComponentId);
    }

    template<class T>
    void RemoveComponent (const Entity& entity)
    {
        unsigned int EntityId = entity.GetId();

        ComponentPool<T>& pool = GetPool<T>();

        ComponentInEntity[EntityId].reset(GetComponentID<T>());
        pool.RemoveComponent(EntityId);
    }
};