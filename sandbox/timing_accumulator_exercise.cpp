#include <cassert>

#include <sapphire/timing_accumulator.hpp>
#include <sapphire/bus_types.hpp>

using namespace sapphire;

int main()
{
    TimingAccumulator acc;

    BusAccessResult r1{};
    r1.timing.time_cost = 2;

    BusAccessResult r2{};
    r2.timing.time_cost = 3;

    assert(acc.total_cost() == 0);

    acc.record(r1);
    assert(acc.total_cost() == 2);

    acc.record(r2);
    assert(acc.total_cost() == 5);

    acc.clear();
    assert(acc.total_cost() == 0);

    return 0;
}
