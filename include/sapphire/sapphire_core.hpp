#pragma once

#include <mythril/kernel.hpp>
#include <mythril/component.hpp>

#include <sapphire/core.hpp>

namespace sapphire {

class SapphireCore final : public Core {
    
public:
    explicit SapphireCore(mythril::Kernel& kernel);

    void step() override;
    mythril::Kernel& kernel() override;

private:
    mythril::Kernel& kernel_;
};

} // namespace sapphire

