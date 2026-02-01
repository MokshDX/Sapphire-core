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

        //1. Advance exactly one scheduling tick
        kernel_.step();

        //2. Enforce accumulated hardware After the tick
        const std::uint64_t accumulated_time = timing_.total_cost();

        for(std::uint64_t i=0; i < accumulated_time; ++i){
            kernel_.step();
        }
        //3. Explicity clear timing boundry
        timing_.clear();
    }

    void SapphireCore::record_bus_timing(const BusAccessResult& result)
    {
        if (state_ != State::Running)
        {
            return;
        }

        timing_.record(result);
        
    }

    SapphireCore::State SapphireCore::state() const
    {
        return state_;
    }

} // namespace sapphire
