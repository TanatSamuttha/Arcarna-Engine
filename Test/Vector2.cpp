#include "Assert.hpp"
#include "Math/Math.hpp"

int main ()
{
    using Vector2 = Arcarna::Math::Vector2;

    Vector2 u(1, 5);
    Vector2 v(2, 4);

    Assert(true, Vector2(3.0f, 9.0f) == u + v, "u + v");
    Assert(true, Vector2(-1.0f, 1.0f) == u - v, "u - v");
    Assert(true, Vector2(2.0f, 20.0f) == u * v, "u * v");
    Assert(true, Vector2(0.5f, 5.0f/4) == u / v, "u / v");
    Assert(22.0f, Vector2::Dot(u, v), "u . v");
    Assert(-6.0f, Vector2::Cross(u, v), "u x v");

    return 0;
}