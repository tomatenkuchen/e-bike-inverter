#include "hal-sensors.hpp"
#include "main.h"
#include "motor.hpp"
#include "stm32g4xx_hal_gpio.h"
#include <mp-units/systems/angular.h>
#include <mp-units/systems/angular/units.h>
#include <mp-units/systems/si/units.h>
#include <numbers>

namespace units = mp_units::angular::unit_symbols;
using namespace mp_units;

namespace bsp
{

constexpr auto sector_size = std::numbers::pi / 3 * units::rad;

HallSensor::HallSensor()
    : latest{.sector = get_sector_from_gpios(), .timestamp = 0 * si::second},
      old{.sector = get_sector_from_gpios(), .timestamp = 0 * si::second}
{
}

void HallSensor::interrupt_handler(quantity<si::second, float> system_time)
{
    old = latest;
    latest = Point{
        .sector = get_sector_from_gpios(),
        .timestamp = system_time,
    };

    auto const delta_t = latest.timestamp - old.timestamp;
    auto const speed = sector_size / delta_t;

    MotorState new_motor{
        .position = sector_size * latest,
        .speed = speed,
        .acceleration = (speed - motor.speed) / delta_t,
    };

    motor = new_motor;
}

MotorState HallSensor::get_motor_state(quantity<si::second, float> system_time)
{
    auto const delta_t = system_time - latest.timestamp;
    auto const new_speed = motor.acceleration * delta_t;
    auto const new_pos = new_speed * delta_t;

    MotorState new_motor = {
        .position = new_pos,
        .speed = new_speed,
        .acceleration = motor.acceleration,
    };

    return new_motor;
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