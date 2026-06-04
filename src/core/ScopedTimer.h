//
// Created by Tharmiga Loganathan on 2026-06-04.
//

#pragma once

#include <chrono>

// RAII timer that writes elapsed milliseconds when it leaves scope.
//
class ScopedTimer {
public:
    explicit ScopedTimer(float& outputMilliseconds)
        : outputMilliseconds(outputMilliseconds),
          startTime(std::chrono::high_resolution_clock::now()) {}

    ~ScopedTimer() {
        // Store elapsed time in the referenced output variable.
        //
        const auto endTime = std::chrono::high_resolution_clock::now();
        const auto elapsed = endTime - startTime;

        outputMilliseconds = std::chrono::duration<float, std::milli>(elapsed).count();
    }

    ScopedTimer(const ScopedTimer&) = delete;
    ScopedTimer& operator=(const ScopedTimer&) = delete;

private:
    float& outputMilliseconds;
    std::chrono::high_resolution_clock::time_point startTime;
};

