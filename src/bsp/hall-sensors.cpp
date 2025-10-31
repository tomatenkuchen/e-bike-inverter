#include "hall-sensors.hpp"
#include "main.h"
#include "stm32g4xx_hal_gpio.h"
#include <numbers>
#include <stdexcept>

namespace bsp
{

HallSensor::HallSensor()
    : sector{get_sector_from_gpios()}
{
}

void HallSensor::interrupt_handler()
{
    sector = get_sector_from_gpios();
}

int8_t HallSensor::get_sector() const
{
    return sector;
}

int8_t HallSensor::get_sector_from_gpios()
{
    auto h1 = HAL_GPIO_ReadPin(HALL1_GPIO_Port, HALL1_Pin) == GPIO_PIN_SET;
    auto h2 = HAL_GPIO_ReadPin(HALL2_GPIO_Port, HALL2_Pin) == GPIO_PIN_SET;
    auto h3 = HAL_GPIO_ReadPin(HALL3_GPIO_Port, HALL3_Pin) == GPIO_PIN_SET;

    uint8_t sec = 0;
    sec += h1 ? 1 : 0;
    sec += h2 ? 2 : 0;
    sec += h3 ? 4 : 0;

    if (sec == 0 || sec == 0x7)
    {
        // normal hall operation can never result in all hall 0 or 1
        throw std::runtime_error("invalid hall sensor state");
    }

    return sec;
}

} // namespace bsp