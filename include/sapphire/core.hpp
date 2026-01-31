#pragma once

namespace mythril {
    class Kernel;
}

namespace sapphire {

class Core {
public:
    virtual ~Core() = default;

    //Advance the emulated machine by one externally-authorized time step
    virtual void step() = 0;

    virtual mythril::Kernel& kernel() = 0;
    
};

} // namespace sapphire
