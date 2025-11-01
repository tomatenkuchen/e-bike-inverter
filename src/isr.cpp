#include "main.h"
#include "main.hpp"
#include "stm32g4xx_hal_gpio.h"
#include "stm32g4xx_hal_tim.h"
#include <chrono>
#include <cstdint>
#include <span>

using namespace std::chrono_literals;

std::chrono::milliseconds system_time = 0ms;

extern ADC_HandleTypeDef hadc1;
extern ADC_HandleTypeDef hadc2;
extern CORDIC_HandleTypeDef hcordic;
extern CRC_HandleTypeDef hcrc;
extern DMA_HandleTypeDef hdma_adc1;
extern DMA_HandleTypeDef hdma_adc2;
extern DMA_HandleTypeDef hdma_usart2_rx;
extern DMA_HandleTypeDef hdma_usart2_tx;
extern FDCAN_HandleTypeDef hfdcan1;
extern FMAC_HandleTypeDef hfmac;
extern TIM_HandleTypeDef htim1;
extern TIM_HandleTypeDef htim8;
extern UART_HandleTypeDef huart2;

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
    adc1_2_ = 3,
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
    lptim1_ = 6,
    spi3_ = 6,
    uart4,
    tim6_dac_ = 6,
    tim7,
    dma2_channel1,
    dma2_channel2,
    dma2_channel3,
    dma2_channel4,
    dma2_channel5,
    ucpd1 = 7,
    comp1_2_3,
    comp4,
    crs = 9,
    sai1,
    fpu = 9,
    rng = 10,
    lpuart1,
    i2c3_ev,
    i2c3_er,
    dmamux_ovr,
    dma2_channel6 = 11,
    cordic = 11,
    fma
};

constexpr uint32_t interrupt_vector_size = 117;

void system_init()
{
    SCB->CPACR |= ((3UL << (10 * 2)) | (3UL << (11 * 2))); /* set CP10 and CP11 Full Access */

    // SCB->VTOR = VECT_TAB_BASE_ADDRESS | VECT_TAB_OFFSET; /* Vector Table Relocation in Internal SRAM */
}

[[noreturn]] void error_handler()
{
    while (true)
        ;
}

} // namespace

extern "C" void __libc_init_array();
extern "C" void __libc_fini_array();
extern int main();
extern uint8_t _sdata;
extern uint8_t _edata;
extern uint8_t _sidata;
extern uint8_t _sbss;
extern uint8_t _ebss;

extern "C" [[noreturn]] void reset_handler()
{
    std::span const data_ram(&_sdata, &_edata);
    std::span const data_rom(&_sidata, data_ram.size());
    std::span const bss(&_sbss, &_ebss);

    system_init();

    if (!data_rom.empty())
    {
        std::copy(data_rom.begin(), data_rom.end(), data_ram.begin());
    }
    if (!bss.empty())
    {
        std::ranges::fill(bss, 0);
    }

    __libc_init_array();

    main();

    __libc_fini_array();

    error_handler();
}

void systick_handler()
{
    system_time += 1ms;
    HAL_IncTick();
}

void dma1_ch1_handler()
{
    HAL_DMA_IRQHandler(&hdma_adc1);
}

void dma1_ch2_handler()
{
    HAL_DMA_IRQHandler(&hdma_adc2);
}

void dma1_ch3_handler()
{
    HAL_DMA_IRQHandler(&hdma_usart2_rx);
}

void dma1_ch4_handler()
{
    HAL_DMA_IRQHandler(&hdma_usart2_tx);
}

void adc_handler()
{
    HAL_ADC_IRQHandler(&hadc1);
    HAL_ADC_IRQHandler(&hadc2);
}

void tim1_handler()
{
    HAL_TIM_IRQHandler(&htim1);
}

void exti_9_5_handler()
{
    get_bsp().hall->interrupt_handler();
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if (htim == &htim1)
    {
        get_bsp().inverter->interrupt_handler();
    }
}

// fill interrupt vector
constexpr __attribute__((section(".isr_vector"))) std::array<void_func_ptr, interrupt_vector_size> isr_vector_table =
    [] {
        std::array<void_func_ptr, interrupt_vector_size> a;

        // default init all vectors with error handler
        std::ranges::fill(a, error_handler);

        // add handler to address if needed
        a[(int)IsrType::reset] = reset_handler;
        a[(int)IsrType::systick] = systick_handler;
        a[(int)IsrType::dma1_channel1] = dma1_ch1_handler;
        a[(int)IsrType::dma1_channel2] = dma1_ch2_handler;
        a[(int)IsrType::dma1_channel3] = dma1_ch3_handler;
        a[(int)IsrType::dma1_channel4] = dma1_ch4_handler;
        a[(int)IsrType::adc1_2_] = adc_handler;
        a[(int)IsrType::tim1_up_tim16] = tim1_handler;
        a[(int)IsrType::exti9_5] = exti_9_5_handler;

        return a;
    }();
