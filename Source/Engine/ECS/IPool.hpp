#pragma once

class IPool
{
public:
    virtual ~IPool() = default;

    virtual void SwapEntityId (unsigned oldId, unsigned newId) = 0;

    virtual void RemoveComponent (const unsigned int& EntityId) = 0;
};