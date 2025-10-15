/**
 * @file inverter.hpp
 * @brief inverter for power delivery and analog measurement
 */

#pragma once

namespace bsp
{

class Inverter
{
  public:
    Inverter();
    ~Inverter();

  private:
    void adc_init();
    void adc2_init();
    void cordic_init();
    void fmac_init();
    void tim1_init();
    void gpio_init();
};

} // namespace bsp
