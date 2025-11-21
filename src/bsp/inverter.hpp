/**
 * @file inverter.hpp
 * @brief inverter for power delivery and analog measurement
 */

#pragma once

#include <array>
#include <cstdint>
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

    /**
     * @brief set voltages for the 3 phases
     *
     * @param voltages voltages of phase u,v,w
     */
    void set_voltage(std::array<quantity<si::volt, float>, 3> voltages);

    /**
     * @brief get measured phase currrents
     *
     * @return std::array<quantity<si::ampere, float>, 3>
     */
    std::array<quantity<si::ampere, float>, 3> get_currents();

    /**
     * @brief interrupt handler for control loop. it should be processed after adc conversion complete
     */
    void interrupt_handler();

  private:
    struct AdcOutput
    {
        struct Adc1
        {
            uint16_t vbus;
            uint16_t temperature;
            uint16_t poti;
            uint16_t bemf3;
        };
        struct Adc2
        {
            uint16_t bemf1;
            uint16_t bemf2;
        };
        Adc1 adc1;
        Adc2 adc2;
    };

    struct Measurements
    {
        quantity<si::volt, float> vbus;
        quantity<si::degree_Celsius, float> temperature;
        quantity<si::volt, float> poti;
        std::array<quantity<si::ampere, float>, 3> phase_currents;
    };

    Measurements measurements;

    void measure_inputs();

    /**
     * @brief Modulate the outputs to achieve the desired voltages
     *
     * @param voltages input voltages for each phase
     * @return std::array<quantity<si::volt, float>, 3> modulated voltages
     *
     * this function minimizes switching losses for low side mosfets by scaling all voltages to the lowest voltage.
     * necessary for function is an isolated motor system.
     */
    std::array<quantity<si::volt, float>, 3> modulate_outputs(std::array<quantity<si::volt, float>, 3> voltages);

    /**
     * @brief Calculate the duty cycles for the given voltages
     *
     * @param voltages voltages for each phase
     * @param v_bus bus voltage
     * @return std::array<uint32_t, 3> duty cycles for each phase
     */
    std::array<uint32_t, 3> calc_duty(std::array<quantity<si::volt, float>, 3> voltages);
};

} // namespace bsp
