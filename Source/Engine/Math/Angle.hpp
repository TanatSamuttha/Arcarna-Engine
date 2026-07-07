#pragma once

#include <cmath>

namespace Arcarna::Math
{
    float AngleNormalize (float Angle)
    {
        float result = std::fmod(Angle, 360);
        if (result < 0)
            result += 360;
        
            return result;
    }
}