#include "Assert.hpp"
#include "Math/Math.hpp"

int main ()
{
    Assert(0.0f, Arcarna::Math::AngleNormalize(0.0f), "0.0");
    Assert(0.785f, Arcarna::Math::AngleNormalize(0.785f), "0.785");
    Assert(0.785f, Arcarna::Math::AngleNormalize(7.069f), "7.069");
    Assert(0.0f, Arcarna::Math::AngleNormalize(12.566f), "12.566");
    Assert(5.498f, Arcarna::Math::AngleNormalize(-0.785f), "-0.785");
    Assert(5.498f, Arcarna::Math::AngleNormalize(-7.069f), "-7.069");
    Assert(6.274f, Arcarna::Math::AngleNormalize(-12.576f), "-12.576");

    return 0;
}