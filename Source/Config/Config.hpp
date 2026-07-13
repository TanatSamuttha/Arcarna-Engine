#pragma once

#include <string>

namespace Arcarna::Config
{
    static constexpr unsigned int FPS = 60;
    static constexpr unsigned int WindowWidth = 640;
    static constexpr unsigned int WindowHeight = 480;
    static constexpr std::string WindowName = "My Game";

    bool IsRunning;
}