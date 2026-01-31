#include <iostream>

#include <mythril/kernel.hpp>
#include <sapphire/sapphire_core.hpp>

// Sandbox-only dummy component
#include <sandbox/dummy_component.hpp>

int main()
{
    // Kernel: authoritative time source
    mythril::Kernel kernel;

    // Core: authoritative machine
    sapphire::SapphireCore core(kernel);

    // Dummy hardware component (sandbox only)
    sandbox::DummyComponent dummy;

    std::cout << "=== Positive lifecycle tests ===\n\n";


    std::cout << "Initial state:\n";
    std::cout << "  core state = " << static_cast<int>(core.state()) << "\n";
    std::cout << "  kernel tick = " << kernel.tick() << "\n";
    std::cout << "  dummy step count = " << dummy.step_count() << "\n\n";

    // ---- Construction phase ----
    core.add_component(&dummy);

    // Freeze topology
    core.freeze();

    std::cout << "After freeze:\n";
    std::cout << "  core state = " << static_cast<int>(core.state()) << "\n";
    std::cout << "  kernel tick = " << kernel.tick() << "\n";
    std::cout << "  dummy step count = " << dummy.step_count() << "\n\n";

    // Start execution
    core.start();

    std::cout << "After start:\n";
    std::cout << "  core state = " << static_cast<int>(core.state()) << "\n";
    std::cout << "  kernel tick = " << kernel.tick() << "\n";
    std::cout << "  dummy step count = " << dummy.step_count() << "\n\n";

    // ---- Running phase ----
    core.step();

    std::cout << "After one core.step():\n";
    std::cout << "  core state = " << static_cast<int>(core.state()) << "\n";
    std::cout << "  kernel tick = " << kernel.tick() << "\n";
    std::cout << "  dummy step count = " << dummy.step_count() << "\n\n";

    return 0;
}
