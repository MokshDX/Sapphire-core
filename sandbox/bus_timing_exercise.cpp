#include <cassert>

#include <mythril/kernel.hpp>
#include <sandbox/dummy_component.hpp>
#include <sapphire/sapphire_core.hpp>
#include <sapphire/bus_types.hpp>

using namespace sapphire;
using namespace sandbox;

int main()
{
    mythril::Kernel kernel;
    SapphireCore core(kernel);

    DummyComponent dummy;
    core.add_component(&dummy);

    // Before freeze/start, nothing should happen
    BusAccessResult access{};
    access.timing.time_cost = 5;

    core.enforce_bus_timing(access);
    assert(kernel.tick() == 0);
    assert(dummy.step_count() == 0);

    // Start machine
    core.freeze();
    core.start();

    assert(kernel.tick() == 0);

    // Enforce bus timing
    core.enforce_bus_timing(access);

    // Exactly 5 ticks must have advanced
    assert(kernel.tick() == 5);
    assert(dummy.step_count() == 5);

    return 0;
}
