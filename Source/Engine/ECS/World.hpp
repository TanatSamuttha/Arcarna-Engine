#pragma once

#include <unordered_map>
#include <vector>
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

    inline static unsigned int NextComponentId = 0;

    inline static std::vector<std::unique_ptr<Entity>> Entities;
    inline static std::vector<std::bitset<MAX_COMPONENT>> ComponentInEntity;
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

        Entities.emplace_back(std::move(entity_ptr));
        ComponentInEntity.emplace_back();
        entity.SetId(Entities.size());

        return entity;
    }

    inline static void DestroyEntity (Entity& entity)
    {
        unsigned int EntityId = entity.GetId();
        std::bitset<MAX_COMPONENT>& Components = ComponentInEntity[EntityId];

        for (int i = 0; i < ComponentPools.size(); ++i)
        {
            if (Components.test(i))
            {
                ComponentPools[i]->RemoveComponent(EntityId);
            }
        }

        size_t last = Entities.size() - 1;

        if (EntityId != last)
        {
            Entities[EntityId] = std::move(Entities[last]);
            ComponentInEntity[EntityId] = std::move(ComponentInEntity[last]);
            
            Components = ComponentInEntity[EntityId];
            
            for (int i = 0; i < ComponentPools.size(); ++i)
            {
                if (Components.test(i))
                {
                    ComponentPools[i].get()->SwapEntityId(EntityId, last);
                }
            }

            Entities[EntityId].get()->SetId(EntityId);
        }
        Entities.pop_back();
        ComponentInEntity.pop_back();
    }

    template<class T, class... Args>
    inline static void AddComponent (const Entity& entity, Args&&... args)
    {   
        ComponentPool<T>& pool = GetPool<T>();
        
        unsigned int EntityId = entity.GetId();

        ComponentInEntity[EntityId].set(GetComponentID<T>());
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

        ComponentInEntity[EntityId].reset(GetComponentID<T>());
        pool.RemoveComponent(EntityId);
    }
};