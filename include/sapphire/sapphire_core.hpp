#pragma once

#include <vector>

#include <mythril/kernel.hpp>
#include <mythril/component.hpp>
#include <sapphire/bus_types.hpp>
#include <sapphire/timing_accumulator.hpp>
namespace sapphire {

    class SapphireCore final {

        public:
            // Lifecycle states of the core
            enum class State {
                Constructing,
                Frozen,
                Running
            };

            // Construct a core bound to a kernel.
            // Enters Constructing state.
            explicit SapphireCore(mythril::Kernel& kernel);

            // ---- Construction phase ----

            // Register a hardware component in execution order.
            // Allowed only in Constructing state.
            void add_component(mythril::Component* component);

            // Freeze the machine topology.
            // Transitions Constructing -> Frozen.
            void freeze();

            // ---- Execution phase ----

            // Start execution.
            // Transitions Frozen -> Running.
            void start();

            // Advance the machine by exactly one kernel tick.
            // Allowed only in Running state.
            void step();

            //Explicit timing enforcement
            void record_bus_timing(const BusAccessResult& result);

            // ---- Introspection ----

            // Return current lifecycle state.
            State state() const;

        private:
            mythril::Kernel& kernel_;
            State state_;

            // Ordered list of hardware components owned by the core.
            std::vector<mythril::Component*> components_;

            TimingAccumulator timing_;
    };

} // namespace sapphire