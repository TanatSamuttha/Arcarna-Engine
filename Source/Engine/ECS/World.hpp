#pragma once

#include <unordered_map>
#include <typeindex>
#include <memory>

#include "IPool.hpp"
#include "ComponentPool.hpp"
#include "Entity.hpp"

class World
{
private:
    inline static unsigned int NextEntityId = 0;
    inline static unsigned int NextComponentId = 0;

    inline static std::vector<std::unique_ptr<Entity>> Entities;
    inline static std::vector<std::unique_ptr<IPool>> ComponentPools;

    template<class T>
    inline static unsigned int GetComponentID ()
    {
        static unsigned int id = NextComponentId++;
        return id;
    }

    template<class T>
    inline static ComponentPool<T>& GetPool ()
    {
        unsigned int ComponentId = GetComponentID<T>();

        if (ComponentId == ComponentPools.size())
            ComponentPools.push_back(std::make_unique<ComponentPool<T>>());

        return *static_cast<ComponentPool<T>*>(ComponentPools[ComponentId].get());
    }

public:
    inline static Entity& NewEntity ()
    {
        auto entity_ptr = std::make_unique<Entity>();

        Entity& entity = *entity_ptr;

        Entities.push_back(std::move(entity_ptr));
        entity.SetId(NextEntityId++);

        return entity;
    }

    template<class T>
    inline static void AddComponent (const Entity& entity)
    {
        ComponentPool<T>& pool = GetPool<T>();
        
        unsigned int EntityId = entity.GetId();

        pool.AddComponent(EntityId);
    }

    template<class T, class... Args>
    inline static void AddComponent (const Entity& entity, Args&&... args)
    {
        unsigned int ComponentId = GetComponentID<T>();
        
        ComponentPool<T>& pool = GetPool<T>();
        
        unsigned int EntityId = entity.GetId();

        pool.AddComponent(EntityId, std::forward<Args>(args)...);
    }

    template<class T>
    inline static T& GetComponent (const Entity& entity)
    {
        unsigned int ComponentId = GetComponentID<T>();
        
        ComponentPool<T>& pool = GetPool<T>();

        return pool.GetComponent(entity.GetId());
    }

    template<class T>
    inline static void RemoveComponent (const Entity& entity)
    {
        unsigned int EntityId = entity.GetId();

        ComponentPool<T>& pool = GetPool<T>();

        pool.RemoveComponent(EntityId);
    }
};