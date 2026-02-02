#include <cassert>

#include <mythril/kernel.hpp>

#include <sapphire/sapphire_core.hpp>
#include <sapphire/bus.hpp>
#include <sapphire/bus_types.hpp>
#include <sapphire/cpu.hpp>

using namespace sapphire;

namespace sandbox {

class FakeBus final : public Bus {
    public:
        explicit FakeBus(SapphireCore& core)
            : core_(core) {}

        BusAccessResult read(std::uint32_t) override {
            BusAccessResult r{};
            r.kind = BusAccessKind::Read;
            r.timing.time_cost = 1;

            core_.record_bus_timing(r);
            ++reads_;
            return r;
        }

        BusAccessResult write(std::uint32_t, std::uint32_t) override {
            BusAccessResult r{};
            r.kind = BusAccessKind::Write;
            r.timing.time_cost = 1;

            core_.record_bus_timing(r);
            ++writes_;
            return r;
        }

        std::uint32_t reads() const { return reads_; }
        std::uint32_t writes() const { return writes_; }

    private:
        SapphireCore& core_;
        std::uint32_t reads_  = 0;
        std::uint32_t writes_ = 0;
    };

} // namespace sandbox

int main()
{
    mythril::Kernel kernel;
    SapphireCore core(kernel);

    sandbox::FakeBus bus(core);
    Cpu cpu(bus);

    core.add_component(&cpu);
    core.freeze();
    core.start();

    // Initial state
    assert(kernel.tick() == 0);
    assert(bus.reads() == 0);

    // Step 1: Fetch
    core.step();
    assert(bus.reads() == 1);
    assert(kernel.tick() == 2); // 1 scheduling + 1 bus timing

    // Step 2: Decode (no bus)
    core.step();
    assert(bus.reads() == 1);
    assert(kernel.tick() == 3); // scheduling only

    // Step 3: Execute (no bus, pc++)
    core.step();
    assert(kernel.tick() == 4);

    // Step 4: Execute completed, no fetch yet
    core.step();
    assert(bus.reads() == 1);
    assert(kernel.tick() == 5);

    // Step 5: Next Fetch
    core.step();
    assert(bus.reads() == 2);
    assert(kernel.tick() == 7);


    return 0;
}