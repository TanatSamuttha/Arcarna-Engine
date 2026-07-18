#pragma once

namespace Arcarna::Math
{
    class Vector2
    {
    public:
        float x = 0.0f;
        float y = 0.0f;

        inline Vector2 () = default;

        inline Vector2 (const float x, const float y) : x(x), y(y) {}
    
        inline Vector2 operator+ (const Vector2& other) const
        {
            return Vector2(x + other.x, y + other.y);
        }

        inline Vector2 operator- (const Vector2& other) const
        {
            return Vector2(x - other.x, y - other.y);
        }

        inline Vector2 operator* (const Vector2& other) const
        {
            return Vector2(x * other.x, y * other.y);
        }

        inline Vector2 operator* (const float multiplier) const
        {
            return Vector2(x * multiplier, y * multiplier);
        }

        inline Vector2 operator/ (const Vector2& other) const
        {
            return Vector2(x / other.x, y / other.y);
        }

        inline Vector2 operator/ (const float denominator) const
        {
            return Vector2(x / denominator, y / denominator);
        }

        inline bool operator== (const Vector2& other) const
        {
            return (x == other.x && y == other.y);
        }

        inline void operator+= (const Vector2& other)
        {
            this->x += other.x;
            this->y += other.y;
        }

        inline static float Dot (Vector2& u, Vector2& v)
        {
            return (u.x * v.x) + (u.y * v.y);
        }

        inline static float Cross (Vector2& u, Vector2& v)
        {
            return (u.x * v.y) - (u.y * v.x);
        }
    };
}