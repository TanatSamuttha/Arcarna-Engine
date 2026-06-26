#pragma once

#include <iostream>
#include <vector>

class Entity
{
private:
    unsigned int id = -1;
public:
    Entity () = default;

    ~Entity () = default;

    void SetId (const unsigned int& id)
    {
        this->id = id;
    }

    unsigned int GetId () const
    {
        return id;
    }
};