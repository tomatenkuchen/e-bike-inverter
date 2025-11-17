#include "core.hpp"
#include "gpio.h"
#include "main.h"
#include <array>
#include <cstdint>
#include <stdexcept>

using namespace mp_units;

extern "C" void SystemClock_Config();

namespace bsp
{

Core::Core()
{
    HAL_Init();
    SystemClock_Config();
    MX_GPIO_Init();
}

Core::~Core()
{
    HAL_DeInit();
}

void Core::wait_for_interrupt()
{
    __WFI();
}

quantity<si::milli<si::second>, uint32_t> Core::get_system_time()
{
    return HAL_GetTick() * si::milli<si::second>;
}

} // namespace bsp
