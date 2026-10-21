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
