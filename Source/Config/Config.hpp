#pragma once

#include <string_view>

namespace Arcarna::Config
{
    static constexpr unsigned int FPS = 60;
    static constexpr float WindowWidth = 640;
    static constexpr float WindowHeight = 480;
    static constexpr float Aspect = WindowWidth / WindowHeight;
    static constexpr std::string_view WindowName = "My Game";

    static bool IsRunning;
}