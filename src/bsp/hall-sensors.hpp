/**
 * @file hal-sensors.hpp
 * @brief driver for hal motor position input
 */
#pragma once

#include <cstdint>

namespace bsp
{

class HallSensor
{
  public:
    /**
     * @brief should be called on an interrupt (or a poll) that triggers on a state change of one of the hall inputs
     */
    void interrupt_handler();

    /**
     * @brief returns the most recent motor sector
     */
    int8_t get_sector() const;

  private:
    int8_t sector = 0;

    int8_t get_sector_from_gpios();
};

} // namespace bsp