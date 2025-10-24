###############################################################################
# add cmsis library
add_library(cmsis INTERFACE)

target_include_directories(cmsis INTERFACE
  ${CMAKE_CURRENT_SOURCE_DIR}/Drivers/Drivers/CMSIS/Include
  ${CMAKE_CURRENT_SOURCE_DIR}/Drivers/Drivers/CMSIS/Device/ST/STM32G4xx/Include
)

target_compile_definitions(cmsis INTERFACE
  USE_HAL_DRIVER
  STM32G431xx
)

###############################################################################
# add stm hal
add_library(stm32g4-hal STATIC
  ${CMAKE_CURRENT_SOURCE_DIR}/Drivers/Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_hal_adc.c
  ${CMAKE_CURRENT_SOURCE_DIR}/Drivers/Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_hal_adc_ex.c
  ${CMAKE_CURRENT_SOURCE_DIR}/Drivers/Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_hal.c
  ${CMAKE_CURRENT_SOURCE_DIR}/Drivers/Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_hal_cordic.c
  ${CMAKE_CURRENT_SOURCE_DIR}/Drivers/Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_hal_cortex.c
  ${CMAKE_CURRENT_SOURCE_DIR}/Drivers/Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_hal_crc.c
  ${CMAKE_CURRENT_SOURCE_DIR}/Drivers/Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_hal_crc_ex.c
  ${CMAKE_CURRENT_SOURCE_DIR}/Drivers/Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_hal_dma.c
  ${CMAKE_CURRENT_SOURCE_DIR}/Drivers/Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_hal_dma_ex.c
  ${CMAKE_CURRENT_SOURCE_DIR}/Drivers/Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_hal_exti.c
  ${CMAKE_CURRENT_SOURCE_DIR}/Drivers/Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_hal_fdcan.c
  ${CMAKE_CURRENT_SOURCE_DIR}/Drivers/Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_hal_flash.c
  ${CMAKE_CURRENT_SOURCE_DIR}/Drivers/Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_hal_flash_ex.c
  ${CMAKE_CURRENT_SOURCE_DIR}/Drivers/Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_hal_flash_ramfunc.c
  ${CMAKE_CURRENT_SOURCE_DIR}/Drivers/Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_hal_fmac.c
  ${CMAKE_CURRENT_SOURCE_DIR}/Drivers/Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_hal_gpio.c
  ${CMAKE_CURRENT_SOURCE_DIR}/Drivers/Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_hal_opamp.c
  ${CMAKE_CURRENT_SOURCE_DIR}/Drivers/Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_hal_opamp_ex.c
  ${CMAKE_CURRENT_SOURCE_DIR}/Drivers/Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_hal_pwr.c
  ${CMAKE_CURRENT_SOURCE_DIR}/Drivers/Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_hal_pwr_ex.c
  ${CMAKE_CURRENT_SOURCE_DIR}/Drivers/Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_hal_rcc.c
  ${CMAKE_CURRENT_SOURCE_DIR}/Drivers/Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_hal_rcc_ex.c
  ${CMAKE_CURRENT_SOURCE_DIR}/Drivers/Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_hal_tim.c
  ${CMAKE_CURRENT_SOURCE_DIR}/Drivers/Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_hal_tim_ex.c
  ${CMAKE_CURRENT_SOURCE_DIR}/Drivers/Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_hal_uart.c
  ${CMAKE_CURRENT_SOURCE_DIR}/Drivers/Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_hal_uart_ex.c
  ${CMAKE_CURRENT_SOURCE_DIR}/Drivers/Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_ll_adc.c

  ${CMAKE_CURRENT_SOURCE_DIR}/Drivers/Core/Src/main.c
  ${CMAKE_CURRENT_SOURCE_DIR}/Drivers/Core/Src/stm32g4xx_hal_msp.c
  ${CMAKE_CURRENT_SOURCE_DIR}/Drivers/Core/Src/system_stm32g4xx.c
)

target_include_directories(stm32g4-hal
  PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/Drivers/Drivers/STM32G4xx_HAL_Driver/Inc
    ${CMAKE_CURRENT_SOURCE_DIR}/Drivers/Core/Inc/
)

target_link_libraries(stm32g4-hal PUBLIC cmsis)

