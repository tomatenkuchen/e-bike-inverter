#include "main.hpp"
#include "core.hpp"
#include "inverter.hpp"
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
    bsp::Can can;

    // init hall sensors
    bsp::HallSensor hall;

    // make available to interrupt handlers
    bspptr = BspPointer{
        .can = &can,
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
