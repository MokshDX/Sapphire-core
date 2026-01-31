#pragma once

#include <cstdint>
#include <mythril/component.hpp>

namespace sandbox {

struct DummyComponent : public mythril::Component
{
    std::uint64_t step_count_ = 0;

    void step() override
    {
        ++step_count_;
    }

    std::uint64_t step_count() const
    {
        return step_count_;
    }
};

} // namespace sapphire
