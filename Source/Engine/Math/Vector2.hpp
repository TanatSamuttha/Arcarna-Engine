#pragma once

namespace Arcarna::Math
{
    class Vector2
    {
    public:
        float x = 0.0f;
        float y = 0.0f;

        Vector2 () = default;

        Vector2 (const float x, const float y) : x(x), y(y) {}
    
        Vector2 operator+ (const Vector2& other) const
        {
            return Vector2(x + other.x, y + other.y);
        }

        Vector2 operator- (const Vector2& other) const
        {
            return Vector2(x - other.x, y - other.y);
        }

        Vector2 operator* (const Vector2& other) const
        {
            return Vector2(x * other.x, y * other.y);
        }

        Vector2 operator/ (const Vector2& other) const
        {
            return Vector2(x / other.x, y / other.y);
        }

        Vector2 operator/ (const float denominator) const
        {
            return Vector2(x / denominator, y / denominator);
        }

        bool operator== (const Vector2& other) const
        {
            return (x == other.x && y == other.y);
        }

        void operator+= (const Vector2& other)
        {
            this->x += other.x;
            this->y += other.y;
        }

        static float Dot (Vector2& u, Vector2& v)
        {
            return (u.x * v.x) + (u.y * v.y);
        }

        static float Cross (Vector2& u, Vector2& v)
        {
            return (u.x * v.y) - (u.y * v.x);
        }
    };
}