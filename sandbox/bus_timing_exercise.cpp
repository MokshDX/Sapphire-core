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

    core.freeze();
    core.start();

    //Initial state
    assert(kernel.tick() == 0);
    assert(dummy.step_count() == 0);

    // Record bus timing
    BusAccessResult access{};
    access.timing.time_cost = 5;

    core.record_bus_timing(access);

    //Enforce timing by stepping 
    core.step();

    // Exactly 5 ticks must have advanced
    assert(kernel.tick() == 6); // 1 for the step() call + 5 for the timing
    assert(dummy.step_count() == 6); // DummyComponent should have stepped 6 times, absorbing the timing delay

    return 0;
}