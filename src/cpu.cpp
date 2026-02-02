#include <sapphire/cpu.hpp>

namespace sapphire {

Cpu::Cpu(Bus& bus)
    : bus_(bus)
{
}

void Cpu::step()
{
    switch (phase_) {

        case Phase::Fetch: {
            // Perform one observable action
            bus_.read(pc_);

            // After a bus access, hardware must wait
            wait_remaining_ = 1;  // fake for now
            phase_ = Phase::Wait;
            break;
        }

        case Phase::Decode: {
            // Fake decode
            ir_ = 0x00;

            phase_ = Phase::Execute;
            break;
        }

        case Phase::Execute: {
            // Fake execute
            ++pc_;

            phase_ = Phase::Fetch;
            break;
        }

        case Phase::Wait: {
            // Absorb enforced timing ticks
            if (wait_remaining_ > 0) {
                --wait_remaining_;
                return;
            }

            // Resume real work
            phase_ = Phase::Decode;
            break;
        }
    }
}

} // namespace sapphire
