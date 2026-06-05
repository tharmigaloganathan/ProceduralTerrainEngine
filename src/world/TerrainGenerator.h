//
// Created by Tharmiga Loganathan on 2026-06-02.
//

#pragma once

#include "world/ChunkCoord.h"

#include <cstdint>
#include <vector>

// Generation parameters kept together so terrain can later be controlled by UI,
// serialized to disk, or passed to worker threads.
//
struct TerrainSettings {
    int resolution = 80;
    float spacing = 0.25f;

    float frequency = 0.35f;
    float heightScale = 1.5f;

    float waterHeight = -0.4f;
    float grassHeight = 0.5f;
    float rockHeight = 1.1f;
};

struct TerrainMeshData {
    // Interleaved vertex data:
    // position.x, position.y, position.z, color.r, color.g, color.b
    //
    std::vector<float> vertices;
    std::vector<std::uint32_t> indices;
};

class TerrainGenerator {
public:
    TerrainMeshData generate(const TerrainSettings& settings, ChunkCoord coord) const;

private:
    float heightAt(float x, float z, const TerrainSettings& settings) const;
    void appendColorForHeight(
        std::vector<float>& vertices,
        float height,
        const TerrainSettings& settings
        ) const;
};

