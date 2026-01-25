#include "core.hpp"
#include "inverter.hpp"
#include "main.hpp"
#include "uart-interface.hpp"

BspPointer bspptr;

BspPointer get_bsp()
{
    return bspptr;
}

int main()
{
    // initialize cpu
    bsp::Core core;

    // initialize inverter
    bsp::Inverter inverter;

    // init coms
    bsp::Uart uart;

    // init hall sensors
    bsp::HallSensor hall;

    // make available to interrupt handlers
    bspptr = BspPointer{
        .core = &core,
        .hall = &hall,
        .inverter = &inverter,
        .uart = &uart,
    };

    while (true)
    {
        core.wait_for_interrupt();
    }

    return 0;
}
