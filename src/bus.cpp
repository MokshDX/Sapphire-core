#include <sapphire/bus.hpp>

namespace sapphire {

// Trivial stub bus used only for early validation.
class StubBus final : public Bus {
public:
    BusAccessResult read(std::uint32_t /*address*/) override {
        BusAccessResult result{};
        result.kind = BusAccessKind::Read;
        result.timing.time_cost = 1; // dummy abstract cost
        result.flags = {};
        result.value = 0xFF;
        return result;
    }

    BusAccessResult write(std::uint32_t /*address*/,
                          std::uint32_t /*value*/) override {
        BusAccessResult result{};
        result.kind = BusAccessKind::Write;
        result.timing.time_cost = 1; // dummy abstract cost
        result.flags = {};
        result.value.reset();
        return result;
    }
};

} // namespace sapphire
