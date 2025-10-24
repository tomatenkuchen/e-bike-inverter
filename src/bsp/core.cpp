#include "core.hpp"
#include "main.h"
#include <array>
#include <cstdint>
#include <stdexcept>

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


} // namespace bsp
