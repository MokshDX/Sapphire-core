#include <sapphire/sapphire_core.hpp>

namespace sapphire {

    SapphireCore::SapphireCore(mythril::Kernel& kernel)
        : kernel_(kernel),
        state_(State::Constructing)
    {
    }

    void SapphireCore::add_component(mythril::Component* component)
    {
        if (state_ != State::Constructing) {
            return;
        }

        components_.push_back(component);
    }

    void SapphireCore::freeze()
    {
        if (state_ != State::Constructing) {
            return;
        }

        // Register all components with the kernel in fixed order
        for (mythril::Component* component : components_) {
            kernel_.register_component(component);
        }

        state_ = State::Frozen;
    }

    void SapphireCore::start()
    {
        if (state_ != State::Frozen) {
            return;
        }

        kernel_.start();
        state_ = State::Running;
    }

    void SapphireCore::step()
    {
        if (state_ != State::Running) {
            return;
        }

        kernel_.step();
    }

    void SapphireCore::enforce_bus_timing(const BusAccessResult& result)
    {
        if (state_ != State::Running)
        {
            return;
        }

        //Explicit,auditable timing enforcement
        for (std::uint64_t i = 0; i < result.timing.time_cost; ++i)
        {
            kernel_.step();
        }
        
    }

    SapphireCore::State SapphireCore::state() const
    {
        return state_;
    }

} // namespace sapphire
