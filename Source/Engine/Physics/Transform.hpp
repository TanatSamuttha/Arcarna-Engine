#pragma once

#include <cmath>

#include "Math/Math.hpp"

class Transform
{
    using Vector3 = Arcarna::Math::Vector3;

private:
    int current, previous = 1;

    Vector3 Position;
    Vector3 Scale;
    float Rotation;

public:
    bool Active = true;

    Transform () : Position(Vector3(0, 0, 0)), Rotation(0), Scale(Vector3(1, 1, 0)) {}

    Transform (Vector3& Position, float Rotation, Vector3& Scale) : Position(Position), Rotation(Arcarna::Math::AngleNormalize(Rotation)), Scale(Scale) {}

    void SetRotation (float Rotation)
    {
        this->Rotation = Arcarna::Math::AngleNormalize(Rotation);
    }

    float GetRotation ()
    {
        return this->Rotation;
    }

    void SetPosition (const Vector3& Position)
    {
        this->Position = Position;
    }

    Vector3 GetPosition ()
    {
        return Position;
    }

    void SetScale (const Vector3& Scale)
    {
        this->Scale = Scale;
    }

    Vector3 GetScale ()
    {
        return Scale;
    }
};