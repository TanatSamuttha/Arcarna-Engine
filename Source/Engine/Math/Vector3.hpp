#pragma once

namespace Arcarna::Math
{
    class Vector3
    {
    public:
        float x = 0.0f;
        float y = 0.0f;
        float z = 0.0f;

        inline Vector3 () = default;

        inline Vector3 (const float x, const float y, const float z) : x(x), y(y), z(z) {}
    
        inline Vector3 operator+ (const Vector3& other) const
        {
            return Vector3(x + other.x, y + other.y, z + other.z);
        }

        inline Vector3 operator- (const Vector3& other) const
        {
            return Vector3(x - other.x, y - other.y, z - other.z);
        }

        inline Vector3 operator* (const Vector3& other) const
        {
            return Vector3(x * other.x, y * other.y, z * other.z);
        }

        inline Vector3 operator* (const float multiplier) const
        {
            return Vector3(x * multiplier, y * multiplier, z * multiplier);
        }

        inline Vector3 operator/ (const Vector3& other) const
        {
            return Vector3(x / other.x, y / other.y, z / other.z);
        }

        inline Vector3 operator/ (const float denominator) const
        {
            return Vector3(x / denominator, y / denominator, z / denominator);
        }

        inline bool operator== (const Vector3& other) const
        {
            return (x == other.x && y == other.y && z == other.z);
        }

        inline void operator+= (const Vector3& other)
        {
            this->x += other.x;
            this->y += other.y;
            this->z += other.z;
        }

        inline static float Dot (Vector3& u, Vector3& v)
        {
            return (u.x * v.x) + (u.y * v.y) + (u.z * v.z);
        }

        inline static Vector3 Cross (const Vector3& u, const Vector3& v)
        {
            return Vector3(
                (u.y * v.z) - (u.z * v.y),
                (u.z * v.x) - (u.x * v.z),
                (u.x * v.y) - (u.y * v.x)
            );
        }
    };
}