/**
 * @file core.hpp
 * @brief contains close to cpu peripheral controls to startup controller
 */

#pragma once

#include "mp-units.hpp"
#include "mp-units/si/time.hpp"

using namespace mp_units;

namespace bsp
{

class Core
{
  public:
    Core();

    ~Core();

    void wait_for_interrupt();

    si::milliseconds get_system_time();

  private:
};

} // namespace bsp
