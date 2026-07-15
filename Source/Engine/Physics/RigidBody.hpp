#pragma once

#include <stdexcept>

#include "Math/Math.hpp"

class RigidBody
{
    using Vector2 = Arcarna::Math::Vector2;

private:
    static const unsigned int ImpulseMode = 1;

    Vector2 Velocity;
    Vector2 Force;

    float Mass;

public:
    bool Active = true;

    RigidBody () : Velocity(Vector2(0, 0)), Force(Vector2(0, 0)), Mass(1) {}

    RigidBody (const float Mass) : Velocity(Vector2(0, 0)), Force(Vector2(0, 0)), Mass(Mass) {}

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

    Vector2 GetForce ()
    {
        return Force;
    }

    void ResetForce ()
    {
        Force = Vector2(0, 0);
    }
};