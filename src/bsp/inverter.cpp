#include "inverter.hpp"
#include "main.h"
#include "mp-units/systems/si.h"
#include "stm32g4xx_hal_gpio.h"
#include "stm32g4xx_hal_tim.h"
#include <cstdint>
#include <mp-units/systems/si/units.h>
#include <stdexcept>

using namespace mp_units;
extern TIM_HandleTypeDef htim1;

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

void Inverter::set_voltage(std::array<quantity<si::volt, float>, 3> voltages)
{
    TIM_OC_InitTypeDef channel_cfg = {
        .OCMode = TIM_OCMODE_PWM1,
        .Pulse = static_cast<uint32_t>((voltages[0].number() / 48.0f) * static_cast<float>(htim1.Init.Period)),
        .OCPolarity = TIM_OCPOLARITY_HIGH,
        .OCFastMode = TIM_OCFAST_DISABLE,
    };
    HAL_TIM_PWM_ConfigChannel(&htim1, &channel_cfg, TIM_CHANNEL_1);
}

std::array<quantity<si::ampere, float>, 3> Inverter::get_currents()
{
    return {0 * si::volt, 0 * si::volt, 0 * si::volt};
}

void Inverter::interrupt_handler()
{
    // measure current states
    //
    // get new set point
    //
    // speed control
    //
    // current control
    //
    // end of control loop
}

void Inverter::measure_inputs()
{
}

} // namespace bsp
