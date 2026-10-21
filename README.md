# Arcarna-Engine

A custom game engine written in C++20, built incrementally with an emphasis on understanding and controlling core engine systems rather than relying on a large game-engine framework.

## Overview

Arcarna is a work-in-progress engine project currently centered on a lightweight, OpenGL-based rendering path and a custom entity-component architecture. It brings together scene organization, entities and components, sprite rendering, and basic physics and simulation in one codebase. The project also explores performance-oriented techniques such as instanced rendering and GPU computation, including CUDA experiments for selected workloads.

## Design Focus

- **Control over core systems:** Build engine mechanisms directly and keep dependencies focused.
- **Performance-conscious implementation:** Consider data layout, rendering overhead, and opportunities for parallel execution.
- **Incremental development:** Keep systems understandable and testable as engine features grow.

## Current Scope

- **Language:** C++20
- **Rendering:** OpenGL, using GLFW for window and context management and GLAD for function loading
- **Image handling:** STB Image
- **Architecture:** A custom entity-component system and scene management
- **Simulation:** Basic transform and rigid-body-style physics, with ongoing exploration of GPU-assisted computation

## Project Status

Arcarna is actively evolving; its systems and interfaces may change as implementation and experiments progress.

## Entry Point

`main()` is the engine's entry point and controls the top-level application loop:

- **Frame pacing:** Calculates the target frame interval from `Arcarna::Config::FPS` and schedules each frame using `std::chrono` and `std::this_thread::sleep_until`.
- **Startup:** Sets `Arcarna::Config::IsRunning` to `true` and calls `System::Start()` before entering the loop.
- **Per-frame update:** While the running flag remains `true`, measures the elapsed time since the previous timestamp and passes it in seconds as `dt` to `System::Update(dt)`.
- **Loop termination:** The loop continues until `Arcarna::Config::IsRunning` becomes `false`.

The target frame interval is used to pace the loop, while `dt` reflects measured elapsed time and may vary from frame to frame. The entry point currently has no explicit system shutdown call; the loop exits when the running flag is cleared.

## Configuration

`Config.hpp` groups the engine's basic application settings under `Arcarna::Config`:

- **Target frame rate (`FPS`):** Set to `60` and used by the entry point to calculate the target frame interval.
- **Window dimensions (`WindowWidth`, `WindowHeight`):** Set the initial window size to `640 × 480`.
- **Aspect ratio (`Aspect`):** Calculated from the configured width and height, giving a `4:3` ratio for the current defaults.
- **Window title (`WindowName`):** Defaults to `"My Game"`.
- **Running state (`IsRunning`):** A mutable Boolean flag used as the entry point's main-loop condition.

The dimensions, title, and target frame rate define the current defaults; `IsRunning` represents runtime state rather than a compile-time setting.

**Implementation note:** Because `IsRunning` is declared as a namespace-scope `static` variable in a header, each translation unit that includes the header gets its own copy. If multiple `.cpp` files need to observe or change the same running state, the flag must be arranged to have shared storage.
