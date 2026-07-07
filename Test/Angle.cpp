#include "Assert.hpp"
#include "Math/Math.hpp"

int main ()
{
    Assert(0.0f, Arcarna::Math::AngleNormalize(0), "0.0");
    Assert(45.0f, Arcarna::Math::AngleNormalize(45), "45.0");
    Assert(40.0f, Arcarna::Math::AngleNormalize(400.0f), "400.0");
    Assert(0.0f, Arcarna::Math::AngleNormalize(720.0), "720.0");
    Assert(315.0f, Arcarna::Math::AngleNormalize(-45), "-45.0");
    Assert(320.0f, Arcarna::Math::AngleNormalize(-400), "400.0");
    Assert(359.5f, Arcarna::Math::AngleNormalize(-720.5), "-720.5");

    return 0;
}