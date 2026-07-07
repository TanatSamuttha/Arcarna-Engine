#pragma once

#include <stdexcept>

#include "Math/Math.hpp"

class RigidBody
{
    using Vector2 = Arcarna::Math::Vector2;

private:
    const unsigned int ImpulseMode = 1;

    Vector2 Velocity;
    Vector2 Force;

    float Mass;

public:
    RigidBody () = default;

    void SetMass (const float Mass)
    {
        if (Mass < 0)
            throw std::runtime_error("Mass can't be nagative");
        this->Mass = Mass;
    }

    float GetMass ()
    {
        return Mass;
    }

    void SetVelocity (const Vector2& Velocity)
    {
        this->Velocity = Velocity;
    }

    Vector2 GetVelocity ()
    {
        return Velocity;
    }

    void AddForce (const Vector2& Force, const unsigned int ForceMode)
    {
        if (ForceMode == ImpulseMode)
        {
            Velocity += Force / Mass;
        }
        else
        {
            this->Force += Force;
        }
    }
};