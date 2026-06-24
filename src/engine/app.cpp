#include <chrono>
#include <thread>
#include <iostream>

#include "workspace/script/init.hpp"
#include "engine/setting.hpp"

int main ()
{
    using Clock = std::chrono::steady_clock;

    constexpr auto FrameTime = std::chrono::nanoseconds(1'000'000'000 / Arcarna::Setting::fps);

    Arcarna::Start();

    bool running = true;

    auto nextFrame = Clock::now();

    while (running)
    {
        nextFrame += FrameTime;

        {

        }

        std::this_thread::sleep_until(nextFrame);
    }
    

    return 0;
}