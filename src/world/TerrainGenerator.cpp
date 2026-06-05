//
// Created by Tharmiga Loganathan on 2026-06-02.
//

#include "TerrainGenerator.h"

#include <cmath>

TerrainMeshData TerrainGenerator::generate(
    const TerrainSettings& settings,
    ChunkCoord coord) const {
    TerrainMeshData meshData;

    // Clamp settings to safe minimums so invalid UI/input values cannot break mesh generation.
    //
    const int safeResolution = std::max(settings.resolution, 1);
    const float safeSpacing = std::max(settings.spacing, 0.01f);

    const int vertexCountPerSide = safeResolution + 1;
    const float chunkWorldSize = static_cast<float>(safeResolution) * safeSpacing;
    const float halfSize = chunkWorldSize * 0.5f;

    const float chunkOffsetX = static_cast<float>(coord.x) * chunkWorldSize;
    const float chunkOffsetZ = static_cast<float>(coord.z) * chunkWorldSize;

    // Each vertex stores 6 floats: x, y, z, r, g, b.
    //
    meshData.vertices.reserve(
        static_cast<std::size_t>(vertexCountPerSide * vertexCountPerSide * 6)
        );

    // Generate a regular grid of vertices positioned at this chunk's world offset.
    //
    for (int z = 0; z < vertexCountPerSide; ++z) {
        for (int x = 0; x < vertexCountPerSide; ++x) {
            const float worldX = static_cast<float>(x) * safeSpacing - halfSize + chunkOffsetX;
            const float worldZ = static_cast<float>(z) * safeSpacing - halfSize + chunkOffsetZ;
            const float worldY = heightAt(worldX, worldZ, settings);

            meshData.vertices.push_back(worldX);
            meshData.vertices.push_back(worldY);
            meshData.vertices.push_back(worldZ);

            appendColorForHeight(meshData.vertices, worldY, settings);
        }
    }

    meshData.indices.reserve(static_cast<std::size_t>(safeResolution * safeResolution * 6));

    // Convert each grid cell into two triangles using indexed drawing.
    //
    for (int z = 0; z < safeResolution; ++z) {
        for (int x = 0; x < safeResolution; ++x) {
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

float TerrainGenerator::heightAt(
    float x,
    float z,
    const TerrainSettings& settings
    ) const {
    // Later this function will be replaced with seeded noise.
    //
    return std::sin(x * settings.frequency)
         * std::cos(z * settings.frequency)
         * settings.heightScale;
}

void TerrainGenerator::appendColorForHeight(
    std::vector<float>& vertices,
    float height,
    const TerrainSettings& settings
    ) const {
    // Height bands are a temporary stand-in for future biome classification.
    //
    if (height < settings.waterHeight) {
        // Water
        vertices.push_back(0.1f);
        vertices.push_back(0.25f);
        vertices.push_back(0.8f);
    } else if (height < settings.grassHeight) {
        // Grass
        vertices.push_back(0.2f);
        vertices.push_back(0.65f);
        vertices.push_back(0.25f);
    } else if (height < settings.rockHeight) {
        // Rock/dirt
        vertices.push_back(0.45f);
        vertices.push_back(0.35f);
        vertices.push_back(0.25f);
    } else {
        // Snow/high peaks
        vertices.push_back(0.9f);
        vertices.push_back(0.9f);
        vertices.push_back(0.85f);
    }
}
