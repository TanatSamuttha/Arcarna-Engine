#pragma once

#include <cmath>

#include "Math/Math.hpp"

class Transform
{
    using Vector3 = Arcarna::Math::Vector3;

private:
    Vector3 Position;
    Vector3 Scale;
    Vector3 Rotation;

public:
    bool Active = true;

    Transform () : Position(Vector3(0, 0, 0)), Rotation(Vector3(0, 0, 0)), Scale(Vector3(1, 1, 1)) {}

    Transform (Vector3& Position, Vector3 Rotation, Vector3& Scale) : Position(Position), Rotation(Arcarna::Math::AngleNormalize(Rotation)), Scale(Scale) {}

    void SetRotation (Vector3 Rotation)
    {
        this->Rotation = Arcarna::Math::AngleNormalize(Rotation);
    }

    Vector3 GetRotation ()
    {
        return Rotation;
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