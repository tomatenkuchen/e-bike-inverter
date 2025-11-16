/**
 * @file inverter.hpp
 * @brief inverter for power delivery and analog measurement
 */

#pragma once

#include <array>
#include <cstdint>
#include <mp-units/systems/si.h>
#include <mp-units/systems/si/units.h>

using namespace mp_units;

namespace bsp
{

class Inverter
{
  public:
    Inverter();

    ~Inverter();

    void set_voltage(std::array<quantity<si::volt, float>, 3> voltages);

    std::array<quantity<si::ampere, float>, 3> get_currents();

    void interrupt_handler();

  private:
    struct AdcOutput
    {
        struct Adc1
        {
            uint16_t vbus;
            uint16_t temperature;
            uint16_t poti;
            uint16_t bemf3;
        };
        struct Adc2
        {
            uint16_t bemf1;
            uint16_t bemf2;
        };
        Adc1 adc1;
        Adc2 adc2;
    };

    struct Measurements
    {
        quantity<si::volt, float> vbus;
        quantity<si::degree_celsius, float> temperature;
        quantity<si::volt, float> poti;
        std::array<quantity<si::ampere, float>, 3> phase_currents;
    };

    void measure_inputs();
};

} // namespace bsp
