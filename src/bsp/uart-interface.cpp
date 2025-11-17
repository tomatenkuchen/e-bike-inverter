#include "uart-interface.hpp"
#include "main.h"
#include "usart.h"

extern UART_HandleTypeDef huart2;

namespace bsp
{

Uart::Uart()
{
    MX_USART2_UART_Init();
}

Uart::~Uart()
{
    HAL_UART_DeInit(&huart2);
}

bool Uart::read(std::span<uint8_t> read_data)
{
    if (rx_busy)
    {
        return false;
    }

    rx_busy = true;

    return HAL_UART_Receive_DMA(&huart2, read_data.data(), read_data.size()) == HAL_OK;
}

bool Uart::write(std::span<uint8_t const> data)
{
    if (tx_busy)
    {
        return false;
    }

    tx_busy = true;

    return HAL_UART_Transmit_DMA(&huart2, data.data(), data.size()) == HAL_OK;
}

void Uart::tx_interrupt_hander()
{
    tx_busy = false;
}

void Uart::rx_interrupt_hander()
{
    rx_busy = false;
}
} // namespace bsp