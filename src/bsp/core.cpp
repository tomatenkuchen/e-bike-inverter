#include "core.hpp"
#include "main.h"
#include <array>
#include <cstdint>
#include <stdexcept>

using namespace mp_units;

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

si::milli<si::second> Core::get_system_time()
{
    return si::milli<si::second>(HAL_GetTick());
}

} // namespace bsp
