#include <cassert>

#include <mythril/kernel.hpp>
#include <sapphire/sapphire_core.hpp>
#include <sapphire/bus.hpp>
#include <sandbox/fake_cpu.hpp>

using namespace sapphire;
using namespace sandbox;

int main()
{
    mythril::Kernel kernel;
    SapphireCore core(kernel);

    // Stub bus with deterministic timing
    class StubBus final : public Bus {
    public:
        BusAccessResult read(std::uint32_t) override {
            BusAccessResult r{};
            r.kind = BusAccessKind::Read;
            r.timing.time_cost = 2;
            return r;
        }

        BusAccessResult write(std::uint32_t, std::uint32_t) override {
            BusAccessResult r{};
            r.kind = BusAccessKind::Write;
            r.timing.time_cost = 3;
            return r;
        }
    } bus;

    FakeCPU cpu(bus);

    core.add_component(&cpu);
    core.freeze();
    core.start();

    assert(kernel.tick() == 0);

    // One machine tick
    core.step();

    // Accumulate and enforce timing AFTER the tick
    std::uint64_t total_cost = 0;
    for (const auto& r : cpu.bus_results()) {
        total_cost += r.timing.time_cost;
    }

    for (std::uint64_t i = 0; i < total_cost; ++i) {
        core.step();
    }

    // 1 tick for the CPU step + 5 for bus timing
    assert(kernel.tick() == 6);

    return 0;
}
