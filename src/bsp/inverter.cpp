#include "inverter.hpp"
#include "main.h"
#include "mp-units/systems/si.h"
#include "stm32g4xx_hal_gpio.h"
#include "stm32g4xx_hal_tim.h"
#include <cstdint>
#include <mp-units/systems/si/units.h>
#include <stdexcept>

using namespace mp_units;

namespace bsp
{

uint32_t HAL_RCC_ADC12_CLK_ENABLED = 0;

Inverter::Inverter()
{
    MX_DMA_Init();
    MX_ADC1_Init();
    MX_ADC2_Init();
    MX_CORDIC_Init();
    MX_OPAMP1_Init();
    MX_OPAMP2_Init();
    MX_OPAMP3_Init();
    MX_TIM1_Init();

    // start power source
    HAL_GPIO_WritePin(power_on_GPIO_Port, power_on_Pin, GPIO_PIN_SET);
}

Inverter::~Inverter()
{
    // stop power source
    HAL_GPIO_WritePin(power_on_GPIO_Port, power_on_Pin, GPIO_PIN_RESET);
}

void set_voltage(std::array<quantity<si::volt, float>, 3> voltages)
{
}

std::array<quantity<si::ampere, float>, 3> get_currents()
{
}

void interrupt_handler()
{
}

} // namespace bsp
