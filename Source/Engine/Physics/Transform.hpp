#include "Math/Math.hpp"

class Transform
{
public:
    using Vector2 = Arcarna::Math::Vector2;

    Vector2 Position;
    float Rotation;

    Transform (Vector2& Position, float& Rotation) : Position(Position), Rotation(Rotation) {}
};