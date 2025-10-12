/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32g4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

void HAL_TIM_MspPostInit(TIM_HandleTypeDef *htim);

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define CAN_TERM_Pin GPIO_PIN_14
#define CAN_TERM_GPIO_Port GPIOC
#define VBUS_Pin GPIO_PIN_0
#define VBUS_GPIO_Port GPIOA
#define BEMF1_Pin GPIO_PIN_4
#define BEMF1_GPIO_Port GPIOA
#define BEMF2_Pin GPIO_PIN_4
#define BEMF2_GPIO_Port GPIOC
#define BEMF3_Pin GPIO_PIN_11
#define BEMF3_GPIO_Port GPIOB
#define POTI_Pin GPIO_PIN_12
#define POTI_GPIO_Port GPIOB
#define Temperature_Pin GPIO_PIN_14
#define Temperature_GPIO_Port GPIOB
#define STATUS_Pin GPIO_PIN_6
#define STATUS_GPIO_Port GPIOC
#define CAN_RX_Pin GPIO_PIN_11
#define CAN_RX_GPIO_Port GPIOA
#define BUTTON_Pin GPIO_PIN_10
#define BUTTON_GPIO_Port GPIOC
#define CAN_SHDN_Pin GPIO_PIN_11
#define CAN_SHDN_GPIO_Port GPIOC
#define GPIO_BEMF_Pin GPIO_PIN_5
#define GPIO_BEMF_GPIO_Port GPIOB
#define HALL1_Pin GPIO_PIN_6
#define HALL1_GPIO_Port GPIOB
#define HALL2_Pin GPIO_PIN_7
#define HALL2_GPIO_Port GPIOB
#define HALL3_Pin GPIO_PIN_8
#define HALL3_GPIO_Port GPIOB
#define CAN_TX_Pin GPIO_PIN_9
#define CAN_TX_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
