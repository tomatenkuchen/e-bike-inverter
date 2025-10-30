#include "uart-interface.hpp"
#include "main.h"
#include "stm32g4xx_hal_uart.h"

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
    return HAL_UART_Receive_DMA(&huart2, read_data.data(), read_data.size()) == HAL_OK;
}

bool Uart::write(std::span<uint8_t const> data)
{
    return HAL_UART_Transmit_DMA(&huart2, data.data(), data.size()) == HAL_OK;
}

} // namespace bsp