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
