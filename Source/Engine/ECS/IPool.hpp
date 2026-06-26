#pragma once

class IPool
{
public:
    virtual ~IPool() = default;

    virtual void RemoveComponent (const unsigned int& EntityId) = 0;
};