#include <chrono>
#include <thread>

#include "Config.hpp"
#include "ECS/System.hpp"

class EntryPoint
{
public:
    inline static void Run ()
    {
        using Clock = std::chrono::steady_clock;

        constexpr auto FrameTime = std::chrono::nanoseconds(1'000'000'000 / Arcarna::Config::FPS);

        Arcarna::Config::IsRunning = true;

        auto NextFrame = Clock::now();

        auto Previous = Clock::now();

        System::Start();

        int count = 0;
        while (Arcarna::Config::IsRunning)
        {
            NextFrame += FrameTime;

            double dt = std::chrono::duration<double>(Clock::now() - Previous).count();
            Previous = Clock::now();

            System::Update(dt);

            std::cout << std::chrono::duration<double>(Clock::now() - Previous).count() << '\n';
            std::this_thread::sleep_until(NextFrame);
            ++count;
            if (count == 20)
                break;
        }
    }
};

int main ()
{
    EntryPoint::Run();
    
    return 0;
}