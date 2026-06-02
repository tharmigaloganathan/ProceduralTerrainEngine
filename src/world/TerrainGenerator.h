//
// Created by Tharmiga Loganathan on 2026-06-02.
//

#pragma once

#include <cstdint>
#include <vector>

struct TerrainMeshData {
    std::vector<float> vertices;
    std::vector<std::uint32_t> indices;
};

class TerrainGenerator {
public:
    TerrainMeshData generate(int resolution, float spacing) const;

private:
    float heightAt(float x, float z) const;
};

