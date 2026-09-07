#pragma once

#include <stdexcept>

#include "Math/Math.hpp"

enum class ForceMode : unsigned int
{
    Force,
    Impulse
};

class RigidBody
{
    using Vector3 = Arcarna::Math::Vector3;

private:
    Vector3 Velocity;
    Vector3 Force;

    float Mass;

public:
    bool Active = true;

    RigidBody () : Velocity(Vector3(0, 0, 0)), Force(Vector3(0, 0, 0)), Mass(1) {}

    RigidBody (const float Mass) : Velocity(Vector3(0, 0, 0)), Force(Vector3(0, 0, 0)), Mass(Mass) {}

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

    void SetVelocity (const Vector3& Velocity)
    {
        this->Velocity = Velocity;
    }

    Vector3 GetVelocity ()
    {
        return Velocity;
    }

    void AddForce (const Vector3& Force, ForceMode ForceMode)
    {
        if (ForceMode == ForceMode::Impulse)
        {
            Velocity += Force / Mass;
        }
        else
        {
            this->Force += Force;
        }
    }

    Vector3 GetForce ()
    {
        return Force;
    }

    void ResetForce ()
    {
        Force = Vector3(0, 0, 0);
    }
};