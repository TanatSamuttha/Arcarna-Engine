#include <cmath>

#include "Math/Math.hpp"

class Transform
{
    using Vector2 = Arcarna::Math::Vector2;

private:
    int current, previous = 1;

    Vector2 Position;
    float Rotation;

public:
    Transform (Vector2& Position, float Rotation) : Position(Position), Rotation(Arcarna::Math::AngleNormalize(Rotation)) {}

    void SetRotation (float Rotation)
    {
        this->Rotation = Arcarna::Math::AngleNormalize(Rotation);
    }

    float GetRotation ()
    {
        return this->Rotation;
    }

    Vector2& GetPosition ()
    {
        return Position;
    }
};