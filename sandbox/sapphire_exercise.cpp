#include <iostream>

#include <mythril/kernel.hpp>
#include <sapphire/sapphire_core.hpp>

#include "dummy_component.hpp"

int main()
{
    // Create the kernel (authoritative time source)
    mythril::Kernel kernel;

    // Create the Sapphire core hosted inside the kernel
    sapphire::SapphireCore core(kernel);

    // Create a sandbox-only dummy component
    sandbox::DummyComponent dummy;

    // Register the dummy with the kernel
    kernel.register_component(&dummy);

    // Initial state (pre-execution)
    std::cout << "Initial state:\n";
    std::cout << "  tick = " << kernel.tick() << "\n";
    std::cout << "  dummy step count = " << dummy.step_count() << "\n\n";

    // Start the kernel lifecycle
    kernel.start();

    std::cout << "After start (no stepping):\n";
    std::cout << "  tick = " << kernel.tick() << "\n";
    std::cout << "  dummy step count = " << dummy.step_count() << "\n\n";

    // Advance one authorized step via the core
    core.step();

    std::cout << "After one core.step():\n";
    std::cout << "  tick = " << kernel.tick() << "\n";
    std::cout << "  dummy step count = " << dummy.step_count() << "\n\n";

    return 0;
}
