#include "core.hpp"
#include "inverter.hpp"
#include "motor.hpp"
#include "uart-interface.hpp"
#include "version.hpp"

int main()
{
    // initialize cpu
    bsp::Core core;
    // initialize inverter
    bsp::Inverter inverter;

    while (true)
    {
        core.wait_for_interrupt();
    }

    return 0;
}
