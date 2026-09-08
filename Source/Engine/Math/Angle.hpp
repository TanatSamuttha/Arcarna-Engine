#pragma once

#include <cmath>
#include <numbers>

#include "Math/Vector3.hpp"

namespace Arcarna::Math
{
    inline float AngleNormalize (float Rad)
    {
        float result = std::fmod(Rad, 2 * std::numbers::pi_v<float>);
        if (result < 0)
            result += 2 * std::numbers::pi_v<float>;
        
        return result;
    }

    inline Vector3 AngleNormalize (Vector3 Rads)
    {
        return Vector3(
            AngleNormalize(Rads.x),
            AngleNormalize(Rads.y),
            AngleNormalize(Rads.z)
        );
    }

    inline float DegtoRad (float Degree)
    {
        return Degree / 180 * 2 * std::numbers::pi_v<float>;
    }
}