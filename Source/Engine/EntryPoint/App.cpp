#include <chrono>
#include <thread>
#include <iostream>

#include "Script/init.hpp"
#include "EntryPoint/Setting.hpp"
#include "Scheduler/Scheduler.hpp"

int main ()
{
    using Clock = std::chrono::steady_clock;

    constexpr auto FrameTime = std::chrono::nanoseconds(1'000'000'000 / Arcarna::Setting::FPS);

    Arcarna::Start();

    Arcarna::Setting::IsRunning = true;

    auto NextFrame = Clock::now();

    auto Now = Clock::now();

    while (Arcarna::Setting::IsRunning)
    {
        NextFrame += FrameTime;

        double dt = std::chrono::duration<double>(Clock::now() - Now).count();
        Now = Clock::now();

        Scheduler::Update(dt);

        std::this_thread::sleep_until(NextFrame);
    }
    

    return 0;
}