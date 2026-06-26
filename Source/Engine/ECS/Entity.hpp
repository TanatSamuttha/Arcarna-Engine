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

    void SetId (unsigned int id)
    {
        if (this->id == -1)
        {
            this->id = id;
        }
    }

    unsigned int GetId ()
    {
        return id;
    }
};