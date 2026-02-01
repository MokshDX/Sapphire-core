#include <cassert>
#include <mythril/kernel.hpp>
#include <mythril/component.hpp>
#include <sapphire/sapphire_core.hpp>
#include <sapphire/bus.hpp>
#include <sapphire/bus_types.hpp>

using namespace sapphire;

namespace sandbox {

    class FakeBus final : public Bus {
        public:
            explicit FakeBus(SapphireCore& core)
                : core_(core) {}

            BusAccessResult read(std::uint32_t) override {
                BusAccessResult r{};
                r.kind = BusAccessKind::Read;
                r.timing.time_cost = 2;

                core_.record_bus_timing(r);
                return r;
            }

            BusAccessResult write(std::uint32_t, std::uint32_t) override {
                BusAccessResult r{};
                r.kind = BusAccessKind::Write;
                r.timing.time_cost = 3;

                core_.record_bus_timing(r);
                return r;
            }

        private:
            SapphireCore& core_;
        };

        class FakeComponent final : public mythril::Component {
            public:
                explicit FakeComponent(Bus& bus)
                    : bus_(bus) {}

                void step() override {
                    bus_.read(0x1000);
                    bus_.write(0x2000, 0xAB);
                }

        private:
            Bus& bus_;
        };

} // namespace sandbox

int main()
{
    mythril::Kernel kernel;
    SapphireCore core(kernel);

    sandbox::FakeBus bus(core);
    sandbox::FakeComponent cpu(bus);

    core.add_component(&cpu);
    core.freeze();
    core.start();

    // Initial State
    assert(kernel.tick() == 0);

    /*
    1 scheduling tick
    CPU does:
      - bus read (2 ticks)
      - bus write (3 ticks)
    Total accumulated time: 6 ticks
    */
    core.step();
    assert(kernel.tick() == 6);

    return 0;
}