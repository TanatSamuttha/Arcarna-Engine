#pragma once

namespace Arcarna::Math
{
    class Vector4
    {
    public:
        float x = 0.0f;
        float y = 0.0f;
        float z = 0.0f;
        float w = 0.0f;

        inline Vector4 () = default;

        inline Vector4 (const float x, const float y, const float z) : x(x), y(y), z(z), w(1) {}

        inline Vector4 (const float x, const float y, const float z, const float w) : x(x), y(y), z(z), w(w) {}
    
        inline Vector4 operator+ (const Vector4& other) const
        {
            return Vector4(x + other.x, y + other.y, z + other.z, w + other.w);
        }

        inline Vector4 operator- (const Vector4& other) const
        {
            return Vector4(x - other.x, y - other.y, z - other.z, w - other.w);
        }

        inline Vector4 operator* (const Vector4& other) const
        {
            return Vector4(x * other.x, y * other.y, z * other.z, w * other.w);
        }

        inline Vector4 operator* (const float multiplier) const
        {
            return Vector4(x * multiplier, y * multiplier, z * multiplier, w * multiplier);
        }

        inline Vector4 operator/ (const Vector4& other) const
        {
            return Vector4(x / other.x, y / other.y, z / other.z, w / other.w);
        }

        inline Vector4 operator/ (const float denominator) const
        {
            return Vector4(x / denominator, y / denominator, z / denominator, w / denominator);
        }

        inline bool operator== (const Vector4& other) const
        {
            return (x == other.x && y == other.y && z == other.z && w == other.w);
        }

        inline void operator+= (const Vector4& other)
        {
            this->x += other.x;
            this->y += other.y;
            this->z += other.z;
            this->w += other.w;
        }

        inline static float Dot (Vector4& u, Vector4& v)
        {
            return (u.x * v.x) + (u.y * v.y) + (u.z * v.z) + (u.w, v.w);
        }
    };
}