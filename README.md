# Procedural Terrain Simulation Engine

A C++ real-time procedural terrain simulation engine built with OpenGL, GLM, and Dear ImGui. The project is designed to explore terrain generation, seeded biome systems, chunk-based world streaming, background terrain generation, thread-safe job queues, serialization, and live performance instrumentation.

## Current Status

Day 1 milestone complete:

- Created initial C++ application structure
- Set up GLFW window and OpenGL context
- Integrated GLAD for OpenGL function loading
- Added RAII wrappers for window, shader, and mesh resources
- Loaded and compiled GLSL shaders from disk
- Rendered first OpenGL triangle
- Handled framebuffer resize events for correct viewport updates

Day 2 milestone complete:

- Integrated GLM for 3D vector and matrix math
- Added camera class with position, yaw/pitch rotation, view matrix, and perspective projection
- Updated shaders to use model and view-projection matrices
- Added keyboard-based camera movement with delta-time scaling
- Added input wrapper around GLFW key polling
- Generalized mesh rendering to support multiple OpenGL draw modes
- Generated and rendered a procedural 3D debug grid using line primitives
- Enabled depth testing for 3D rendering
- Updated framebuffer-aware aspect ratio handling for correct perspective projection

Day 3 milestone complete:

- ⁠Added procedural terrain mesh generation
- ⁠Generated grid-based terrain vertices in world space
- ⁠Built triangle index data for terrain surface rendering
- ⁠Extended mesh wrapper to support indexed drawing with element buffers
- ⁠Rendered first generated terrain patch using OpenGL triangles
- ⁠Added basic height function for early terrain variation
- ⁠Prepared terrain generation structure for future noise, biomes, and chunks

## Planned Features

- GLM-based camera and transform math
- Procedural terrain mesh generation
- Seeded biome generation
- Chunk-based terrain loading and unloading
- Background terrain generation workers
- Thread-safe job queue for terrain chunk generation
- Dear ImGui debug and control panels
- Live performance metrics and profiling
- Save/load support for world generation settings

## Tech Stack

- C++
- OpenGL
- GLFW
- GLAD
- GLM
- Dear ImGui
- CMake

## Build

Build instructions will be added as the project setup stabilizes.

## Project Goal

The goal of this project is to build a technically deep C++ simulation engine that demonstrates real-time rendering, procedural generation, resource management, concurrency, serialization, and performance-focused systems design.
