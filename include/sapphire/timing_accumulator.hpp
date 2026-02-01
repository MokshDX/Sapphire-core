#pragma once

#include <cstdint>

#include <sapphire/bus_types.hpp>

namespace sapphire {

// Pure accumulator. No policy. No kernel knowledge.
class TimingAccumulator {
public:
    // Record timing information from a bus access
    void record(const BusAccessResult& result);

    // Total accumulated cost for the current tick
    std::uint64_t total_cost() const;

    // Explicit boundary between ticks
    void clear();

private:
    std::uint64_t total_cost_ = 0;
};

} // namespace sapphire