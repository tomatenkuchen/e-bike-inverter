#include "adc.h"
#include "cordic.h"
#include "crc.h"
#include "dma.h"
#include "fmac.h"
#include "gpio.h"
#include "main.h"
#include "main.hpp"
#include "stm32g4xx_it.h"
#include "tim.h"
#include "usart.h"
#include <chrono>
#include <cstdint>
#include <span>

using namespace std::chrono_literals;

// extern init functions
extern "C" void SystemInit();
extern "C" void __libc_init_array();
extern "C" void __libc_fini_array();

// extern ram symbols
extern uint8_t _sdata;
extern uint8_t _edata;
extern uint8_t _sidata;
extern uint8_t _sbss;
extern uint8_t _ebss;

namespace
{

typedef void (*void_func_ptr)(void);

enum class IsrType
{
    reset,
    nmi,
    hardfault,
    memmanage,
    busfault,
    usagefault,
    svc = 10,
    debugmon,
    pendsv = 13,
    systick,
    wwdg,
    pvd_pvm,
    rtc_tamp_lsecss,
    rtc_wkup,
    flash,
    rcc,
    exti0,
    exti1,
    exti2,
    exti3,
    exti4,
    dma1_channel1,
    dma1_channel2,
    dma1_channel3,
    dma1_channel4,
    dma1_channel5,
    dma1_channel6,
    adc1_2 = 33,
    usb_hp,
    usb_lp,
    fdcan1_it0,
    fdcan1_it1,
    exti9_5,
    tim1_brk_tim15,
    tim1_up_tim16,
    tim1_trg_com_tim17,
    tim1_cc,
    tim2,
    tim3,
    tim4,
    i2c1_ev,
    i2c1_er,
    i2c2_ev,
    i2c2_er,
    spi1,
    spi2,
    usart1,
    usart2,
    usart3,
    exti15_10,
    rtc_alarm,
    usbwakeup,
    tim8_brk,
    tim8_up,
    tim8_trg_com,
    tim8_cc,
    lptim1_ = 64,
    spi3_ = 66,
    uart4,
    tim6_dac_ = 69,
    tim7,
    dma2_channel1,
    dma2_channel2,
    dma2_channel3,
    dma2_channel4,
    dma2_channel5,
    ucpd1 = 78,
    comp1_2_3,
    comp4,
    crs = 90,
    sai1,
    fpu = 96,
    rng = 105,
    lpuart1,
    i2c3_ev,
    i2c3_er,
    dmamux_ovr,
    dma2_channel6 = 112,
    cordic = 115,
    fma
};

constexpr uint32_t interrupt_vector_size = 117;

[[noreturn]] void error_handler()
{
    while (true)
        ;
}

void init_ram()
{
    std::span const data_ram(&_sdata, &_edata);
    std::span const data_rom(&_sidata, data_ram.size());
    std::span const bss(&_sbss, &_ebss);

    if (!data_rom.empty())
    {
        std::copy(data_rom.begin(), data_rom.end(), data_ram.begin());
    }

    if (!bss.empty())
    {
        std::ranges::fill(bss, 0);
    }
}

} // namespace

extern int main();

extern "C" [[noreturn]] void reset_handler()
{

    SystemInit();

    init_ram();

    __libc_init_array();

    main();

    __libc_fini_array();

    error_handler();
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if (htim == &htim1)
    {
        get_bsp().inverter->interrupt_handler();
    }
}

void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{
    if (huart == &huart1)
    {
        get_bsp().uart->tx_interrupt_hander();
    }
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    if (huart == &huart1)
    {
        get_bsp().uart->rx_interrupt_hander();
    }
}

// fill interrupt vector
__attribute__((section(".isr_vector")))
__attribute__((used)) std::array<void_func_ptr, interrupt_vector_size> const isr_vector_table = [] {
    std::array<void_func_ptr, interrupt_vector_size> a;

    // default init all vectors with error handler
    std::ranges::fill(a, error_handler);

    // add handler to address if needed
    a[(int)IsrType::reset] = reset_handler;
    a[(int)IsrType::systick] = SysTick_Handler;
    a[(int)IsrType::dma1_channel1] = DMA1_Channel1_IRQHandler;
    a[(int)IsrType::dma1_channel2] = DMA1_Channel2_IRQHandler;
    a[(int)IsrType::dma1_channel3] = DMA1_Channel3_IRQHandler;
    a[(int)IsrType::dma1_channel4] = DMA1_Channel4_IRQHandler;
    a[(int)IsrType::adc1_2] = ADC1_2_IRQHandler;
    a[(int)IsrType::tim1_up_tim16] = TIM1_UP_TIM16_IRQHandler;
    a[(int)IsrType::exti9_5] = EXTI9_5_IRQHandler;

    return a;
}();
