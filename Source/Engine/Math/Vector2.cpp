#pragma once

namespace Arcarna::Math
{
    class Vector2
    {
    public:
        float x, y;

        Vector2 (const int x, const int y) : x(x), y(y) {}
    
        Vector2 operator+ (const Vector2 other) const
        {
            return Vector2(x + other.x, y + other.y);
        }

        Vector2 operator- (const Vector2 other) const
        {
            return Vector2(x - other.x, y - other.y);
        }

        Vector2 operator* (const Vector2 other) const
        {
            return Vector2(x * other.x, y * other.y);
        }

        Vector2 operator/ (const Vector2 other) const
        {
            return Vector2(x / other.x, y / other.y);
        }

        static float Dot (Vector2 u, Vector2 v)
        {
            return (u.x * v.x) + (u.y * v.y);
        }

        static float Cross (Vector2 u, Vector2 v)
        {
            return (u.x * v.y) - (u.y * v.x);
        }
    };
}