#include <sapphire/timing_accumulator.hpp>

namespace sapphire {

void TimingAccumulator::record(const BusAccessResult& result)
{
    total_cost_ += result.timing.time_cost;
}

std::uint64_t TimingAccumulator::total_cost() const
{
    return total_cost_;
}

void TimingAccumulator::clear()
{
    total_cost_ = 0;
}

} // namespace sapphire
