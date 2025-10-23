/**
 * @file inverter.hpp
 * @brief inverter for power delivery and analog measurement
 */

#pragma once

#include "mp-units/systems/si.h"
#include <array>

namespace bsp
{

class Inverter
{
  public:
    Inverter();
    ~Inverter();

    void set_voltage(std::array<float, 3> voltages);

  private:
    void adc_init();
    void adc2_init();
    void cordic_init();
    void fmac_init();
    void tim1_init();
    void gpio_init();
};

} // namespace bsp
