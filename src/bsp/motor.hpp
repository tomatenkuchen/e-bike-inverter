/**
 * @file motor.hpp
 * @author tomatenkuchen
 * @brief motor state definitions
 * @date 2025-10-30
 *
 * @copyright Copyright (c) 2025
 */

#pragma once

#include <cstdint>
#include <mp-units/systems/angular.h>
#include <mp-units/systems/isq.h>
#include <mp-units/systems/si.h>
#include <mp-units/systems/si/units.h>

using namespace mp_units;

namespace bsp
{

inline constexpr struct radspeed final : named_unit<"", mag<1> * angular::unit_symbols::rad / si::second>
{
};

inline constexpr struct radacceleration final : named_unit<"", mag<1> * radspeed / si::second>
{
};

struct MotorState
{
    angular::unit_symbols::rad position;
    radspeed speed;
    radacceleration acceleration;
};

} // namespace bsp