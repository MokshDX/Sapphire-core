#pragma once

#include <vector>

#include <mythril/component.hpp>
#include <sapphire/bus.hpp>
#include <sapphire/bus_types.hpp>

namespace sandbox {

class FakeCPU final : public mythril::Component {
public:
    explicit FakeCPU(sapphire::Bus& bus)
        : bus_(bus) {}

    void step() override {
        results_.clear();

        results_.push_back(bus_.read(0x1000));
        results_.push_back(bus_.write(0x2000, 0xAB));
    }

    const std::vector<sapphire::BusAccessResult>& bus_results() const {
        return results_;
    }

private:
    sapphire::Bus& bus_;
    std::vector<sapphire::BusAccessResult> results_;
};

} // namespace sandbox
