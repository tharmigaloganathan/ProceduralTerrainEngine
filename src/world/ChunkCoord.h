//
// Created by Tharmiga Loganathan on 2026-06-04.
//

#pragma once

#include <functional>

// Integer coordinate indentifying a terrain chunk in chunk-space.
//
struct ChunkCoord {
    int x = 0;
    int z = 0;

    bool operator==(const ChunkCoord& other) const {
        return x == other.x && z == other.z;
    }
};

// Hash function so ChunkCoord can be ued as a key in std::unordered_map/set.
//
struct ChunkCoordHash {
    std::size_t operator()(const ChunkCoord& coord) const {
        const std::size_t hashX = std::hash<int>{}(coord.x);
        const std::size_t hashZ = std::hash<int>{}(coord.z);

        return hashX ^ (hashZ << 1);
    }
};
