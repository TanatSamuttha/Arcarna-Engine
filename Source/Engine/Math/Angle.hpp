#pragma once

#include <cmath>
#include <numbers>

namespace Arcarna::Math
{
    float AngleNormalize (float Rad)
    {
        float result = std::fmod(Rad, 2 * std::numbers::pi_v<float>);
        if (result < 0)
            result += 2 * std::numbers::pi_v<float>;
        
        return result;
    }

    float DegtoRad (float Degree)
    {
        return Degree / 180 * 2 * std::numbers::pi_v<float>;
    }
}