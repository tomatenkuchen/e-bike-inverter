/**
 * @file inverter.hpp
 * @brief inverter for power delivery and analog measurement
 */

#pragma once

#include <array>
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
};

} // namespace bsp
