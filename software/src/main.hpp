/**
 * @file main.hpp
 * @brief main application entry point
 */

#pragma once

#include "core.hpp"
#include "hall-sensors.hpp"
#include "inverter.hpp"
#include "uart-interface.hpp"

struct BspPointer
{
    bsp::Core *core;
    bsp::HallSensor *hall;
    bsp::Inverter *inverter;
    bsp::Uart *uart;
};

BspPointer get_bsp();
