#include <cassert>

#include <sapphire/bus_types.hpp>

using namespace sapphire;

int main() {
    BusAccessResult result{};
    result.kind = BusAccessKind::Read;
    result.timing.time_cost = 5;
    result.flags.open_bus = true;
    result.value = 0xAB;

    assert(result.timing.time_cost == 5);
    assert(result.flags.open_bus);
    assert(result.value.has_value());
    assert(result.value.value() == 0xAB);

    return 0;
}
