#include "uart-interface.hpp"
#include "main.h"

namespace bsp
{

Uart::Uart()
{
    MX_USART2_UART_Init();
}

std::span<uint8_t const> Uart::read(std::size_t num_of_bytes)
{
    return std::span<uint8_t const>();
}

void Uart::write(std::span<uint8_t const> data)
{
}

} // namespace bsp