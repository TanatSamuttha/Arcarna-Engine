#pragma once

#include <cmath>

namespace Arcarna::Math
{
    float AngleNormalize (float Rad)
    {
        float result = std::fmod(Rad, 2 * M_PI);
        if (result < 0)
            result += 2 * M_PI;
        
        return result;
    }

    float DegtoRad (float Degree)
    {
        return Degree / 180 * M_PI;
    }
}