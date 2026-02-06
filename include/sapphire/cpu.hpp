#pragma once

#include <cstdint>

#include <mythril/component.hpp>
#include <sapphire/bus.hpp>

namespace sapphire {

class Cpu final : public mythril::Component {
public:
    explicit Cpu(Bus& bus);

    void step() override;

private:
    enum class Phase {
        Fetch,
        Decode,
        Execute,
        Wait
    };

    Bus& bus_;

    Phase phase_ = Phase::Fetch;
    Phase resume_phase_ = Phase::Fetch; // For returning from Wait

    // Registers 
    std::uint16_t pc_ = 0x0000;
    std::uint8_t  ir_ = 0x00;

    // How many enforced timing steps we must absorb
    std::uint64_t wait_remaining_ = 0;

    //Named concept: internal execution delay (not cycles)
    std::uint64_t internal_delay_remaining_ = 0;
};

} // namespace sapphire
