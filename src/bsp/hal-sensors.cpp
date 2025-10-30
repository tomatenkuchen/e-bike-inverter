#include "hal-sensors.hpp"
#include "main.h"
#include "stm32g4xx_hal_gpio.h"
#include <mp-units/systems/angular.h>
#include <mp-units/systems/si/units.h>
#include <numbers>

using units = mp_units::angular::unit_symbols;
using namespace mp_units;

namespace bsp
{

constexpr auto sector_size = std::numbers::pi / 3 * units::rad;

HallSensor::HallSensor()
    : latest{.sector = get_sector_from_gpios(), .timestamp = 0 * si::second},
      old{.sector = get_sector_from_gpios(), .timestamp = 0 * si::second},
{
}

void HallSensor::interrupt_handler(si::second system_time)
{
    old = latest;
    latest = Point{
        .sector = get_sector_from_gpios(),
        .timestamp = system_time,
    };
}

HallSensor::MotorState HallSensor::get_motor_state(si::second system_time)
{
}

uint8_t HallSensor::get_sector_from_gpios()
{
    auto h1 = HAL_GPIO_ReadPin(HALL1_GPIO_Port, HALL1_Pin) == GPIO_PIN_SET;
    auto h2 = HAL_GPIO_ReadPin(HALL2_GPIO_Port, HALL2_Pin) == GPIO_PIN_SET;
    auto h3 = HAL_GPIO_ReadPin(HALL3_GPIO_Port, HALL3_Pin) == GPIO_PIN_SET;

    uint8_t sec = 0;
    sec += h1 ? 1 : 0;
    sec += h2 ? 2 : 0;
    sec += h3 ? 4 : 0;

    return sec;
}

} // namespace bsp