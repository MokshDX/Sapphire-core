#pragma once

#include <cstdint>
#include <sapphire/bus_types.hpp>

namespace sapphire {

// Bus is a mediator.
// It does NOT tick.
// It does NOT own time.
class Bus {
public:
    virtual ~Bus() = default;

    virtual BusAccessResult read(std::uint32_t address) = 0;

    virtual BusAccessResult write(std::uint32_t address,
                                  std::uint32_t value) = 0;
};

} // namespace sapphire
