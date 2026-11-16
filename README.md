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

# Project Structure
The project is organized into three main areas:
- `Config/:` Holds application settings and runtime configuration values.
- `Engine/:` Contains the engine's core systems, including ECS, scene management, rendering, physics, and per-frame updates.
- `Workspace/:` Contains game- or application-specific code built on top of the engine, including initialization and project-level logic.

# Configuration

`Config.hpp` groups the engine's basic application settings under `Arcarna::Config`:

- **Target frame rate (`FPS`):** Set to `60` and used by the entry point to calculate the target frame interval.
- **Window dimensions (`WindowWidth`, `WindowHeight`):** Set the initial window size to `640 × 480`.
- **Aspect ratio (`Aspect`):** Calculated from the configured width and height, giving a `4:3` ratio for the current defaults.
- **Window title (`WindowName`):** Defaults to `"My Game"`.
- **Running state (`IsRunning`):** A mutable Boolean flag used as the entry point's main-loop condition.

The dimensions, title, and target frame rate define the current defaults; `IsRunning` represents runtime state rather than a compile-time setting.

**Implementation note:** Because `IsRunning` is declared as a namespace-scope `static` variable in a header, each translation unit that includes the header gets its own copy. If multiple `.cpp` files need to observe or change the same running state, the flag must be arranged to have shared storage.

# Engine

## Entry Point

`main()` is the engine's entry point and controls the top-level application loop:

- **Frame pacing:** Calculates the target frame interval from `Arcarna::Config::FPS` and schedules each frame using `std::chrono` and `std::this_thread::sleep_until`.
- **Startup:** Sets `Arcarna::Config::IsRunning` to `true` and calls `System::Start()` before entering the loop.
- **Per-frame update:** While the running flag remains `true`, measures the elapsed time since the previous timestamp and passes it in seconds as `dt` to `System::Update(dt)`.
- **Loop termination:** The loop continues until `Arcarna::Config::IsRunning` becomes `false`.

The target frame interval is used to pace the loop, while `dt` reflects measured elapsed time and may vary from frame to frame. The entry point currently has no explicit system shutdown call; the loop exits when the running flag is cleared.

## Entity-Component System (ECS)

Arcarna's ECS separates an entity's identity from the components that hold its data. `World` manages entities, component storage, and component queries; `ComponentPool<T>` stores each component type; and `System` coordinates the engine's per-frame update callbacks. Scene management sits above `World` and provides the active scene context through which the ECS world is accessed. Scene switching and lifecycle details are covered in the Scene section.

### Architecture and data flow

- **`Scene` — scene context:** The current implementation exposes the active ECS world through `Scene::World` and tracks the main camera entity through `Scene::MainCameraEntityId`. A scene stores its own `World` and camera ID; switching scenes moves the active world and camera state between the active storage and the selected scene. This section only describes how Scene relates to ECS; its full API and lifecycle are documented separately.
- **`World` — ECS coordinator:** Owns the entity collection, per-entity component masks, type-specific component pools, the free-entity-ID list, and the API for creating, destroying, inspecting, and querying entities. Components are accessed through `World`, rather than being stored directly in `Entity`.
- **`Entity` — identity and state:** An entity has an unsigned integer ID and public `Alive` and `Active` flags. Its component data is stored separately. Destroying an entity removes components recorded in its mask, marks it not alive and inactive, and returns its ID to the free-ID list for reuse.
- **`ComponentPool<T>` — per-type storage:** Each component type has a separate pool containing a `std::vector<T>`, a parallel sorted vector of entity IDs, and a hash map from entity ID to component index. The component objects are stored contiguously, while the map supports lookup by entity ID.
- **`IPool` — type-erased pool interface:** Allows `World` to own pools of different component types through `std::unique_ptr<IPool>` and remove components without knowing the concrete pool template type.
- **Component masks:** `World` stores a bitset per entity to record component membership. The current representation reserves 128 bits for component type IDs.
- **Views — component queries:** `World::View<Components...>()` starts with the smallest pool among the requested component types, then filters candidates to entities containing all requested types. A range-based loop yields references to the matching `Entity` objects.
- **`System` — update orchestration:** `System::Start()` starts physics, rendering, and mesh subsystems, calls workspace initialization, and registers physics and render callbacks. `System::Update(dt)` assigns `dt` to the physics subsystem and executes callbacks in registration order; in the current startup sequence, physics runs before rendering.

### API reference: `Scene` (ECS relationship only)

| API / member | Description |
|---|---|
| `Scene::World` | Static access point to the active `World`. ECS operations in the current design are performed through this world. |

Scene management is included here only to explain the access path to `World`; scene ownership, camera handling, switching behavior, and lifecycle will be documented in the dedicated Scene section.

### API reference: `World`

| API | Description |
|---|---|
| `NewEntity()` | Creates an entity, reusing an ID from the free-ID list when possible, and returns its ID. |
| `NewEntity<Components...>()` | Creates an entity, default-constructs and attaches each listed component type, and returns the entity ID. |
| `GetEntity(EntityId)` | Returns a reference to the entity with the specified ID. |
| `EntityCount()` | Returns the tracked number of live entities. |
| `DestroyEntity(EntityId)` | Removes components listed in the entity's mask, clears the mask, marks the entity not alive and inactive, and releases its ID for reuse. |
| `AddComponent<T>(EntityId, args...)` | Constructs and attaches a component of type `T`. An overload accepts `const Entity&`. |
| `GetComponent<T>(EntityId)` | Returns a reference to the entity's component of type `T`. |
| `HasComponent<T>(EntityId)` | Checks the entity's component mask for type `T`. |
| `RemoveComponent<T>(EntityId)` | Removes the component of type `T` and clears its bit in the entity's mask. |
| `GetPool<T>()` | Returns the pool for type `T`, creating it if it does not exist. |
| `View<Components...>()` | Creates a range of entities containing every requested component type. At least one type must be specified. |

### API reference: `Entity`

| API / member | Description |
|---|---|
| `Entity()` | Constructs an entity with `Alive == true` and `Active == true`; `World` assigns its ID. |
| `SetId(id)` | Sets the entity ID. |
| `GetId()` | Returns the entity ID. |
| `Alive` | Public flag indicating whether the entity is considered alive. |
| `Active` | Public active-state flag, initially `true`. Views do not automatically exclude inactive entities. |
| Copy and move operations | Copy construction and copy assignment are disabled; move operations are enabled. |

### API reference: `ComponentPool<T>` and `IPool`

| API | Description |
|---|---|
| `AddComponent(EntityId, args...)` | Adds a component and records its index. Entity IDs remain sorted; inserting in the middle shifts later entries and updates their map indices. Throws `std::runtime_error` if the entity already has this component type in the pool. |
| `GetIndex(EntityId)` | Returns the component index, or throws `std::runtime_error` if the entity is not in the pool. |
| `GetComponent(EntityId)` | Returns a mutable reference to the specified component. |
| `GetEntities()` | Returns a mutable reference to the pool's internal sorted entity-ID vector. |
| `RemoveComponent(EntityId)` | Removes the component and updates indices for entries shifted by the removal. Throws `std::runtime_error` if the entity is not in the pool. |
| `IPool::RemoveComponent(EntityId)` | Virtual type-erased removal operation implemented by each concrete component pool. |

### API reference: `System`

| API | Description |
|---|---|
| `AddUpdate(callable)` | Registers a callback to run on each update. |
| `AddUpdate(callable, debugName)` | Registers a callback with a debug name that can be printed by `PrintUpdate()`. |
| `PrintUpdate()` | Prints the stored update names for debugging. |
| `Start()` | Starts physics, rendering, and mesh subsystems, calls `Arcarna::Init()`, and registers physics and render update callbacks. |
| `Update(dt)` | Assigns `dt` to `Arcarna::Physics::dt` and executes registered callbacks in order. The entry point supplies `dt` in seconds. |

### Current implementation notes

- Component pools keep entity IDs sorted. Appending a larger ID is amortized constant time for the vectors, but inserting or removing in the middle shifts elements and updates map indices, so these operations are linear in the affected pool size.
- `GetEntities()` exposes the internal vector by mutable reference. Modifying it directly can desynchronize the entity list, component storage, and index map.
- A view iterates over a pool's internal entity-ID vector. Adding or removing components from that same pool during iteration may invalidate its iterators.
- Views filter by component presence, not by `Entity::Active`; systems must check `Active` explicitly when required.
- The component bitset currently supports 128 component type IDs. The current representation does not support registering component types beyond that limit.
- Component type IDs are cached in template-local static variables, but their initial values are taken from a `World` instance. The implementation should be reviewed before using multiple `World` instances, especially when component types are first registered through different worlds.
- `World` APIs generally assume entity IDs are valid and do not consistently validate invalid or stale IDs before accessing internal vectors.
