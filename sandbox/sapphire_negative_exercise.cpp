#include <iostream>

#include <mythril/kernel.hpp>

#include <sapphire/sapphire_core.hpp>
#include <sandbox/dummy_component.hpp>

int main()
{
    mythril::Kernel kernel;
    sapphire::SapphireCore core(kernel);

    sandbox::DummyComponent early;
    sandbox::DummyComponent late;

    std::cout << "=== Negative lifecycle tests ===\n\n";

    // Step before start
    core.step();

    std::cout << "After step() before start:\n";
    std::cout << "  tick = " << kernel.tick() << "\n";
    std::cout << "  early step count = " << early.step_count() << "\n\n";

    // Constructing phase
    core.add_component(&early);

    // Step before freeze
    core.step();

    std::cout << "After step() before freeze:\n";
    std::cout << "  tick = " << kernel.tick() << "\n";
    std::cout << "  early step count = " << early.step_count() << "\n\n";

    // Freeze topology
    core.freeze();

    // Add component after freeze
    core.add_component(&late);

    // Start execution
    core.start();

    // Valid step
    core.step();

    std::cout << "After start + one valid step:\n";
    std::cout << "  tick = " << kernel.tick() << "\n";
    std::cout << "  early step count = " << early.step_count() << "\n";
    std::cout << "  late step count  = " << late.step_count() << "\n\n";

    return 0;
}
