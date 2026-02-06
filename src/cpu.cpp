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
            // Fetch opcode
            BusAccessResult result = bus_.read(pc_);
            ir_ = static_cast<std::uint8_t>(result.value);
            ++pc_;

            //After any bus access, we must wait for the timing to elapse
            wait_remaining_ = result.timing.time_cost;
            resume_phase_ = Phase::Decode;
            phase_ = Phase::Wait;
            break;
        }

        case Phase::Decode: {
            //only NOP implemented for now
            if (ir_ == 0x00) {
                //NOP requires internal execution delay of 1 tick
                internal_delay_remaining_ = 1; 
                phase_ = Phase::Execute;
            } else {
                //Unimplemented opcode path
                phase_ = Phase::Execute;
            }
            break;
        }

        case Phase::Execute: {
            // Absorb internal execution delay
            if (internal_delay_remaining_ > 0) {
                wait_remaining_ = internal_delay_remaining_;
                internal_delay_remaining_ = 0;
                resume_phase_ = Phase::Fetch;
                phase_ = Phase::Wait;
            } else {
                // For unimplemented opcodes, we just do nothing and move on
                phase_ = Phase::Fetch;
            }
            break;
        }

        case Phase::Wait: {
            // Absorb enforced timing ticks
            if (wait_remaining_ > 0) {
                --wait_remaining_;
                return;
            }

            // Resume real work
            phase_ = resume_phase_;
            break;
        }
    }
}

} // namespace sapphire
