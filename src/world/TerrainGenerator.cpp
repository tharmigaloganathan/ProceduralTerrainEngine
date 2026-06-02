//
// Created by Tharmiga Loganathan on 2026-06-02.
//

#include "TerrainGenerator.h"

#include <cmath>

TerrainMeshData TerrainGenerator::generate(int resolution, float spacing) const {
    TerrainMeshData meshData;

    const int vertexCountPerSide = resolution + 1;
    const float halfSize = static_cast<float>(resolution) * spacing * 0.5f;

    meshData.vertices.reserve(
        static_cast<std::size_t>(vertexCountPerSide * vertexCountPerSide * 3)
        );

    // Convert each grid cell into two triangles using indexed drawing.
    //
    for (int z = 0; z < vertexCountPerSide; ++z) {
        for (int x = 0; x < vertexCountPerSide; ++x) {
            const float worldX = static_cast<float>(x) * spacing - halfSize;
            const float worldZ = static_cast<float>(z) * spacing - halfSize;
            const float worldY = heightAt(worldX, worldZ);

            meshData.vertices.push_back(worldX);
            meshData.vertices.push_back(worldY);
            meshData.vertices.push_back(worldZ);
        }
    }

    // Convert each grid cell into two triangles using indexed drawing.
    //
    meshData.indices.reserve(static_cast<std::size_t>(resolution * resolution * 6));

    for (int z = 0; z < resolution; ++z) {
        for (int x = 0; x < resolution; ++x) {
            const std::uint32_t topLeft = static_cast<std::uint32_t>(z * vertexCountPerSide + x);
            const std::uint32_t topRight = topLeft + 1;
            const std::uint32_t bottomLeft = static_cast<std::uint32_t>((z + 1) * vertexCountPerSide + x);
            const std::uint32_t bottomRight = bottomLeft + 1;

            meshData.indices.push_back(topLeft);
            meshData.indices.push_back(bottomLeft);
            meshData.indices.push_back(topRight);

            meshData.indices.push_back(topRight);
            meshData.indices.push_back(bottomLeft);
            meshData.indices.push_back(bottomRight);
        }
    }

    return meshData;
}

float TerrainGenerator::heightAt(float x, float z) const {
    // Later this function will be replaced with seeded noise.
    //
    return std::sin(x * 0.35f) * std::cos(z * 0.35f) * 1.5f;
}
