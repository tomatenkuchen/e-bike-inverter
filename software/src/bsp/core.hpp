/**
 * @file core.hpp
 * @brief contains close to cpu peripheral controls to startup controller
 */

#pragma once

#include <mp-units/systems/si.h>
#include <mp-units/systems/si/units.h>

using namespace mp_units;

namespace bsp
{

class Core
{
  public:
    Core();

    ~Core();

    void wait_for_interrupt();

    quantity<si::milli<si::second>, uint32_t> get_system_time();

  private:
};

} // namespace bsp
