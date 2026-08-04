#pragma once

#include <string>

namespace Arcarna::Config
{
    static constexpr unsigned int FPS = 60;
    static constexpr float WindowWidth = 640;
    static constexpr float WindowHeight = 480;
    static constexpr float Aspect = WindowWidth / WindowHeight;
    static constexpr std::string WindowName = "My Game";

    static bool IsRunning;
}