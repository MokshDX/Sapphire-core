#include <sapphire/sapphire_core.hpp>

namespace sapphire {

SapphireCore::SapphireCore(mythril::Kernel& kernel)
    : kernel_(kernel)
{
}

void SapphireCore::step()
{
    kernel_.step();
}

mythril::Kernel& SapphireCore::kernel()
{
    return kernel_;
}

} // namespace sapphire
