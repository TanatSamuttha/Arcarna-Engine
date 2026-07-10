#pragma once

namespace Arcarna::Math
{
    class Vector3
    {
    public:
        float x = 0.0f;
        float y = 0.0f;
        float z = 0.0f;

        Vector3 () = default;

        Vector3 (const float x, const float y, const float z) : x(x), y(y), z(z) {}
    
        Vector3 operator+ (const Vector3& other) const
        {
            return Vector3(x + other.x, y + other.y, z + other.z);
        }

        Vector3 operator- (const Vector3& other) const
        {
            return Vector3(x - other.x, y - other.y, z - other.z);
        }

        Vector3 operator* (const Vector3& other) const
        {
            return Vector3(x * other.x, y * other.y, z * other.z);
        }

        Vector3 operator* (const float multiplier) const
        {
            return Vector3(x * multiplier, y * multiplier, z * multiplier);
        }

        Vector3 operator/ (const Vector3& other) const
        {
            return Vector3(x / other.x, y / other.y, z / other.z);
        }

        Vector3 operator/ (const float denominator) const
        {
            return Vector3(x / denominator, y / denominator, z / denominator);
        }

        bool operator== (const Vector3& other) const
        {
            return (x == other.x && y == other.y && z == other.z);
        }

        void operator+= (const Vector3& other)
        {
            this->x += other.x;
            this->y += other.y;
            this->z += other.z;
        }

        static float Dot (Vector3& u, Vector3& v)
        {
            return (u.x * v.x) + (u.y * v.y) + (u.z * v.z);
        }

        static float Cross (Vector3& u, Vector3& v)
        {
            return (u.x * v.y) - (u.y * v.x) - (u.z * v.z);
        }
    };
}