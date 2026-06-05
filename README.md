# Procedural Terrain Simulation Engine

A C++ real-time procedural terrain simulation engine built with OpenGL, GLM, and Dear ImGui. The project is designed to explore terrain generation, seeded biome systems, chunk-based world streaming, background terrain generation, thread-safe job queues, serialization, and live performance instrumentation.

## Architecture Overview

The application is organized into several layers:

- `app/` coordinates the main loop, input updates, terrain settings, metrics, and rendering.
- `platform/` wraps GLFW window creation, context setup, framebuffer sizing, and title updates.
- `input/` provides keyboard polling and one-frame key press detection.
- `render/` owns GPU-facing systems such as shaders, meshes, camera matrices, and scene drawing.
- `world/` generates CPU-side terrain mesh data from configurable terrain settings.
- `core/` contains shared utilities such as performance metrics and scoped timing.

## Controls

- `W/S` - Move camera forward/backward
- `A/D` - Move camera left/right
- `Q/E` - Move camera down/up
- Arrow keys - Rotate camera
- `R` - Regenerate terrain with updated settings

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

Day 4 milestone complete:

- Extended terrain vertices to include per-vertex color data
- Added height-based terrain coloring for water, grass, rock, and snow regions
- Updated mesh vertex layout to support multiple vertex attributes
- Updated GLSL shader pipeline to pass vertex colors from CPU-generated terrain to fragment shader
- Rendered first visually classified terrain surface
- Prepared terrain data format for future biome rules, normals, lighting, and materials

Day 5 milestone complete:

- ⁠Added configurable terrain generation settings
- ⁠Replaced hardcoded terrain resolution, spacing, frequency, and height scale values
- ⁠Updated terrain height generation to use structured parameter input
- ⁠Added terrain mesh regeneration support through the renderer
- ⁠Improved separation between terrain generation data and rendering code
- ⁠Prepared terrain settings pipeline for future Dear ImGui controls, seed input, serialization, and live terrain regeneration

Day 6 milestone complete:

- Added frame timing and FPS tracking
- Added terrain generation timing using scoped performance measurement
- Displayed live performance metrics in the window title
- Added timing data flow from terrain regeneration into the renderer/app layer
- Prepared performance instrumentation for future Dear ImGui panels and chunk-generation profiling

Day 8 milestone complete:

- Added chunk coordinate and terrain chunk abstractions
- Added ChunkManager to own and regenerate terrain chunks
- Moved terrain mesh ownership from Renderer into Chunk
- Updated terrain generation to support chunk world offsets
- Updated renderer to draw chunk-managed terrain
- Preserved terrain regeneration flow through the chunk system
- Prepared architecture for multi-chunk loading, unloading, and streaming

Day 9 milestone complete:

- ⁠Expanded ChunkManager to generate a multi-chunk terrain region
- ⁠Added chunk-radius-based creation of active terrain chunks
- ⁠Generated and rendered a 3x3 chunk grid around the origin
- ⁠Preserved continuous terrain sampling across chunk boundaries using world-space coordinates
- ⁠Updated regeneration flow to rebuild all active chunks from shared terrain settings
- ⁠Prepared chunk management structure for future camera-based loading and unloading

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
