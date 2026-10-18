#include <chrono>
#include <thread>

#include "Config.hpp"
#include "ECS/System.hpp"

int main ()
{
    using Clock = std::chrono::steady_clock;

    constexpr auto FrameTime = std::chrono::nanoseconds(1'000'000'000 / Arcarna::Config::FPS);

    Arcarna::Config::IsRunning = true;

    auto NextFrame = Clock::now();

    auto Previous = Clock::now();

    System::Start();

    while (Arcarna::Config::IsRunning)
    {
        NextFrame += FrameTime;

        double dt = std::chrono::duration<double>(Clock::now() - Previous).count();
        Previous = Clock::now();

        System::Update(dt);

        std::this_thread::sleep_until(NextFrame);

    }
    
    return 0;
}