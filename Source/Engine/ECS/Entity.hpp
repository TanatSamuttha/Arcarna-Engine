#pragma once

#include <iostream>
#include <vector>

class Entity
{
private:
    int id = -1;
public:
    Entity () = default;

    ~Entity () = default;

    void SetId (int id)
    {
        if (this->id == -1)
        {
            this->id = id;
        }
    }

    int GetId ()
    {
        return id;
    }
};