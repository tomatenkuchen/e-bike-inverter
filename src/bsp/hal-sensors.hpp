/**
 * @file hal-sensors.hpp
 * @brief driver for hal motor position input
 */
#pragma once

#include "motor.hpp"
#include <cstdint>
#include <mp-units/systems/si/units.h>

using namespace mp_units;

namespace bsp
{

class HallSensor
{
  public:
    HallSensor();

    /**
     * @brief this should be called on an interrupt (or a poll) that triggers on a state change of one of the hall
     * inputs
     * @param system_time system time at interrupt
     */
    void interrupt_handler(si::second system_time);

    /**
     * @brief Get the motor state
     *
     * @param system_time  system time to the time of state polling
     * @return MotorState motor states
     */
    MotorState get_motor_state(si::second system_time);

  private:
    struct Point
    {
        uint8_t sector;
        quantity<si::milli<si::second>, float> timestamp;
    };

    Point latest;
    Point old;

    uint8_t get_sector_from_gpios();
};
} // namespace bsp