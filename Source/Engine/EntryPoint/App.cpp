#include <chrono>
#include <thread>
#include <iostream>

#include "Script/init.hpp"
#include "EntryPoint/Setting.hpp"

int main ()
{
    using Clock = std::chrono::steady_clock;

    constexpr auto FrameTime = std::chrono::nanoseconds(1'000'000'000 / Arcarna::Setting::FPS);

    Arcarna::Start();

    Arcarna::Setting::IsRunning = true;

    auto NextFrame = Clock::now();

    while (Arcarna::Setting::IsRunning)
    {
        NextFrame += FrameTime;

        {
            
        }

        std::this_thread::sleep_until(NextFrame);
    }
    

    return 0;
}