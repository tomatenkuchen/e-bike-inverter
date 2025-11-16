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
    auto const mod_voltages = modulate_outputs(voltages);

    auto const channel_pwm_duty = calc_duty(mod_voltages);

    TIM_OC_InitTypeDef ch1_cfg = {
        .OCMode = TIM_OCMODE_PWM1,
        .Pulse = channel_pwm_duty[0],
        .OCPolarity = TIM_OCPOLARITY_HIGH,
        .OCFastMode = TIM_OCFAST_DISABLE,
    };
    auto ch2_cfg = ch1_cfg;
    ch2_cfg.Pulse = channel_pwm_duty[1];
    auto ch3_cfg = ch1_cfg;
    ch3_cfg.Pulse = channel_pwm_duty[2];

    HAL_TIM_PWM_ConfigChannel(&htim1, &ch1_cfg, TIM_CHANNEL_1);
    HAL_TIM_PWM_ConfigChannel(&htim1, &ch2_cfg, TIM_CHANNEL_2);
    HAL_TIM_PWM_ConfigChannel(&htim1, &ch3_cfg, TIM_CHANNEL_3);
}

std::array<quantity<si::ampere, float>, 3> Inverter::get_currents()
{
    return {0.f * si::ampere, 0.f * si::ampere, 0.f * si::ampere};
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

std::array<quantity<si::volt, float>, 3> Inverter::modulate_outputs(std::array<quantity<si::volt, float>, 3> voltages)
{
    std::array<quantity<si::volt, float>, 3> mod_volt;

    // look for minimum voltage in input
    std::min_element(voltages.begin(), voltages.end());
    quantity<si::volt, float> v_min = *std::min_element(voltages.begin(), voltages.end());

    // subtract minimum from all voltages
    for (size_t i = 0; i < mod_volt.size(); i++)
    {
        mod_volt[i] = voltages[i] - v_min;
    }

    return mod_volt;
}

std::array<uint32_t, 3> Inverter::calc_duty(std::array<quantity<si::volt, float>, 3> voltages)
{
    std::array<uint32_t, 3> duty_cycles;

    for (size_t i = 0; i < voltages.size(); i++)
    {
        duty_cycles[i] = static_cast<uint32_t>((voltages[i].value() / measurements.vbus) * htim1.Init.Period);
    }

    return duty_cycles;
}

} // namespace bsp
