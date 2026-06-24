#include <chrono>
#include <thread>
#include <iostream>

#include "workspace/script/init.hpp"
#include "engine/setting.hpp"

int main ()
{
    using clock = std::chrono::steady_clock;

    constexpr auto frameTime = std::chrono::nanoseconds(100000000 / Arcarna::Setting::fps);

    Arcarna::Start();

    constexpr bool running = true;

    while (running)
    {
        auto start = clock::now();

        

        auto elapsed = clock::now() - start;

        if (elapsed < frameTime)
        {
            std::this_thread::sleep_for(frameTime - elapsed);
        }
    }
    

    return 0;
}