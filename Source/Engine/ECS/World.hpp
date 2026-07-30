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

    std::vector<Entity> Entities;
    std::vector<std::bitset<MAX_COMPONENT>> ComponentInEntity;
    std::vector<std::unique_ptr<IPool>> ComponentPools;

    template<class T>
    unsigned int GetComponentID ()
    {
        static unsigned int id = NextComponentId++;
        return id;
    }

public:
    template<class... Components>
    unsigned int NewEntity ()
    {
        unsigned int EntityId = NewEntity();
        Entity& ThisEntity = GetEntity(EntityId);

        (AddComponent<Components>(ThisEntity), ...);

        return EntityId;
    }

    unsigned int NewEntity ()
    {
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
        Entities[EntityId].SetId(EntityId);
        Entities[EntityId].Alive = true;
        ComponentInEntity[EntityId] = 0;

        return EntityId;
    }

    Entity& GetEntity (const unsigned int& EntityId)
    {
        return Entities[EntityId];
    }

    void DestroyEntity (const unsigned int& EntityId)
    {
        std::bitset<MAX_COMPONENT>& mask = ComponentInEntity[EntityId];

        for (int i = 0; i < ComponentPools.size(); ++i)
        {
            if (mask.test(i))
            {
                ComponentPools[i]->RemoveComponent(EntityId);
            }
        }

        mask.reset();
        Entities[EntityId].Alive = false;
        FreeIds.push_back(EntityId);
    }
    
    template<class T>
    ComponentPool<T>& GetPool ()
    {
        unsigned int ComponentId = GetComponentID<T>();

        if (ComponentId >= ComponentPools.size())
            ComponentPools.resize(ComponentId + 1);

        if (!ComponentPools[ComponentId])
            ComponentPools[ComponentId] = std::make_unique<ComponentPool<T>>();

        return *static_cast<ComponentPool<T>*>(ComponentPools[ComponentId].get());
    }

    template<class T, class... Args>
    void AddComponent (const Entity& entity, Args&&... args)
    {
        AddComponent<T>(entity.GetId(), std::forward<Args>(args)...);
    }

    template<class T, class... Args>
    void AddComponent (const unsigned int& EntityId, Args&&... args)
    {   
        ComponentPool<T>& pool = GetPool<T>();

        ComponentInEntity[EntityId].set(GetComponentID<T>());
        pool.AddComponent(EntityId, std::forward<Args>(args)...);
    }

    template<class T>
    T& GetComponent (const unsigned int& EntityId)
    {
        unsigned int ComponentId = GetComponentID<T>();
        
        ComponentPool<T>& pool = GetPool<T>();

        return pool.GetComponent(EntityId);
    }

    template<class T>
    bool HasComponent (const unsigned int& EntityId)
    {
        unsigned int ComponentId = GetComponentID<T>();

        return ComponentInEntity[EntityId].test(ComponentId);
    }

    template<class T>
    void RemoveComponent (const unsigned int& EntityId)
    {
        ComponentPool<T>& pool = GetPool<T>();

        ComponentInEntity[EntityId].reset(GetComponentID<T>());
        pool.RemoveComponent(EntityId);
    }

    template<class... Components>
    class ViewClass
    {
    private:
        using iterator = std::vector<unsigned int>::iterator;

        World& world;

        iterator beginIt;
        iterator endIt;

    public:
        ViewClass (iterator beginIt, iterator endIt, World& world) : beginIt(beginIt), endIt(endIt), world(world) {}

        class Iterator
        {
        private:
            World& world;

            iterator currentIt;
            iterator endIt;

            void SearchNext ()
            {
                while (currentIt != endIt && !(world.template HasComponent<Components>(world.GetEntity(*currentIt).GetId()) && ...))
                    currentIt++;
            }

        public:
            Iterator (iterator beginIt, iterator endIt, World& world) : currentIt(beginIt), endIt(endIt), world(world)
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
                return world.GetEntity(*currentIt);
            }
        };

        Iterator begin ()
        {
            return Iterator(beginIt, endIt, world);
        }

        Iterator end ()
        {
            return Iterator(endIt, endIt, world);
        }
    };

    template<class... Components>
    ViewClass<Components...> View ()
    {
        std::vector<unsigned int>::iterator SmallestBegin;
        std::vector<unsigned int>::iterator SmallestEnd;
        size_t MinSize = SIZE_MAX;

        auto FindMin = [&](std::vector<unsigned int>& pool)
        {
            if (pool.size() < MinSize)
            {
                MinSize = pool.size();
                SmallestBegin = pool.begin();
                SmallestEnd = pool.end();
            }
        };

        (FindMin(GetPool<Components>().GetEntities()), ...);

        return ViewClass<Components...>(SmallestBegin, SmallestEnd, *this);
    }
};