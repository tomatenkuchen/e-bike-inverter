/**
 * @file main.hpp
 * @brief main application entry point
 */

#pragma once

#include "can-interface.hpp"
#include "core.hpp"
#include "hal-sensors.hpp"
#include "inverter.hpp"
#include "uart-interface.hpp"

struct BspPointer
{
    bsp::Can *can;
    bsp::Core *core;
    bsp::HallSensor *hall;
    bsp::Inverter *inverter;
    bsp::Uart *uart;
};

BspPointer get_bsp();
