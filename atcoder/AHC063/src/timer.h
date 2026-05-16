// @trace-pilot e9f3de458503db0fb8582658680538fc753ce329
#pragma once

#include <chrono>

class Timer {
public:
    Timer() {
        start_ =
            std::chrono::high_resolution_clock::now();
    }

    double elapsed() const {
        using namespace std::chrono;

        auto now =
            high_resolution_clock::now();

        return duration<double>(
            now - start_
        ).count();
    }

private:
    std::chrono::high_resolution_clock::time_point start_;
};

