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
        r.value = 0x00;                 // NOP
        r.timing.time_cost = 1;         // 1 M-cycle

        core_.record_bus_timing(r);
        ++reads_;
        return r;
    }

    BusAccessResult write(std::uint32_t, std::uint32_t) override {
        return {};
    }

    std::uint32_t reads() const { return reads_; }

private:
    SapphireCore& core_;
    std::uint32_t reads_ = 0;
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

    // Execute one NOP fully
    core.step(); // Fetch -> Wait (for fetch timing)
    core.step(); // Wait for fetch timing to elapse
    core.step(); // Decode
    core.step(); // Execute -> Wait (for internal execution delay)
    

    // Exactly one opcode fetch
    assert(bus.reads() == 1);

    // Advance until instruction completes
    while (bus.reads() == 1) {
        core.step();
    }

    // Now we know the *next* instruction began
    assert(bus.reads() == 2);
        return 0;
}
