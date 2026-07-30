#include <chrono>
#include <thread>
#include <iostream>
#include <stdexcept>

#include "Scripts/init.hpp"
#include "Config.hpp"
#include "Scheduler/Scheduler.hpp"

int main ()
{
    using Clock = std::chrono::steady_clock;

    constexpr auto FrameTime = std::chrono::nanoseconds(1'000'000'000 / Arcarna::Config::FPS);

    Arcarna::Config::IsRunning = true;

    auto NextFrame = Clock::now();

    auto Previous = Clock::now();

    Scheduler::Start();

    while (Arcarna::Config::IsRunning)
    {
        NextFrame += FrameTime;

        double dt = std::chrono::duration<double>(Clock::now() - Previous).count();
        Previous = Clock::now();

        Scheduler::Update(dt);

        std::this_thread::sleep_until(NextFrame);
    }
    
    return 0;
}