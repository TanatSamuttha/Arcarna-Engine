#pragma once

#include <cmath>

#include "Math/Math.hpp"

class Transform
{
    using Vector2 = Arcarna::Math::Vector2;

private:
    int current, previous = 1;

    Vector2 Position;
    Vector2 Scale;
    float Rotation;

public:
    bool Active = true;

    Transform () : Position(Vector2(0, 0)), Rotation(0), Scale(Vector2(1, 1)) {}

    Transform (Vector2& Position, float Rotation, Vector2& Scale) : Position(Position), Rotation(Arcarna::Math::AngleNormalize(Rotation)), Scale(Scale) {}

    void SetRotation (float Rotation)
    {
        this->Rotation = Arcarna::Math::AngleNormalize(Rotation);
    }

    float GetRotation ()
    {
        return this->Rotation;
    }

    void SetPosition (const Vector2& Position)
    {
        this->Position = Position;
    }

    Vector2 GetPosition ()
    {
        return Position;
    }

    void SetScale (const Vector2& Scale)
    {
        this->Scale = Scale;
    }

    Vector2 GetScale ()
    {
        return Scale;
    }
};