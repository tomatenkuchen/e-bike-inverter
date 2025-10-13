#include "core.hpp"
#include "main.h"
#include <stdexcept>

namespace bsp
{
Core::Core()
{
    __HAL_FLASH_PREFETCH_BUFFER_ENABLE();
    if (HAL_InitTick(TICK_INT_PRIORITY) != HAL_OK)
    {
        throw std::runtime_error("systick init failed");
    }
    __HAL_RCC_SYSCFG_CLK_ENABLE();
    __HAL_RCC_PWR_CLK_ENABLE();
    HAL_PWREx_DisableUCPDDeadBattery();

    clock_config();
}

Core::~Core()
{
    __HAL_RCC_APB1_FORCE_RESET();
    __HAL_RCC_APB1_RELEASE_RESET();

    __HAL_RCC_APB2_FORCE_RESET();
    __HAL_RCC_APB2_RELEASE_RESET();

    __HAL_RCC_AHB1_FORCE_RESET();
    __HAL_RCC_AHB1_RELEASE_RESET();

    __HAL_RCC_AHB2_FORCE_RESET();
    __HAL_RCC_AHB2_RELEASE_RESET();

    __HAL_RCC_AHB3_FORCE_RESET();
    __HAL_RCC_AHB3_RELEASE_RESET();
}

void Core::clock_config()
{
    RCC_OscInitTypeDef RCC_OscInitStruct = {0};
    RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

    /** Configure the main internal regulator output voltage
     */
    HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1_BOOST);

    /** Initializes the RCC Oscillators according to the specified parameters
     * in the RCC_OscInitTypeDef structure.
     */
    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
    RCC_OscInitStruct.HSIState = RCC_HSI_ON;
    RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
    RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
    RCC_OscInitStruct.PLL.PLLM = RCC_PLLM_DIV4;
    RCC_OscInitStruct.PLL.PLLN = 85;
    RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
    RCC_OscInitStruct.PLL.PLLQ = RCC_PLLQ_DIV2;
    RCC_OscInitStruct.PLL.PLLR = RCC_PLLR_DIV2;
    if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
    {
        throw std::runtime_error("clock config failed");
    }

    /** Initializes the CPU, AHB and APB buses clocks
     */
    RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

    if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4) != HAL_OK)
    {
        throw std::runtime_error("clock config failed");
    }
}

} // namespace bsp
