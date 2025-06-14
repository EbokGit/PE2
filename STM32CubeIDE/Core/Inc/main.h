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
#include "stm32f3xx_hal.h"

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
#define SSR_Pin GPIO_PIN_2
#define SSR_GPIO_Port GPIOA
#define S1_Pin GPIO_PIN_3
#define S1_GPIO_Port GPIOA
#define S1_EXTI_IRQn EXTI3_IRQn
#define S2_Pin GPIO_PIN_4
#define S2_GPIO_Port GPIOA
#define S2_EXTI_IRQn EXTI4_IRQn
#define S3_Pin GPIO_PIN_5
#define S3_GPIO_Port GPIOA
#define S3_EXTI_IRQn EXTI9_5_IRQn
#define S4_Pin GPIO_PIN_6
#define S4_GPIO_Port GPIOA
#define S4_EXTI_IRQn EXTI9_5_IRQn
#define MAX3485_OUT_Pin GPIO_PIN_9
#define MAX3485_OUT_GPIO_Port GPIOA
#define MAX3485_IN_Pin GPIO_PIN_10
#define MAX3485_IN_GPIO_Port GPIOA
#define MAX3485_EN_Pin GPIO_PIN_11
#define MAX3485_EN_GPIO_Port GPIOA
#define WS2812_Pin GPIO_PIN_3
#define WS2812_GPIO_Port GPIOB
#define TXB_16x2_D7_Pin GPIO_PIN_4
#define TXB_16x2_D7_GPIO_Port GPIOB
#define TXB_16x2_D6_Pin GPIO_PIN_5
#define TXB_16x2_D6_GPIO_Port GPIOB
#define TXB_16x2_D5_Pin GPIO_PIN_6
#define TXB_16x2_D5_GPIO_Port GPIOB
#define TXB_16x2_D4_Pin GPIO_PIN_7
#define TXB_16x2_D4_GPIO_Port GPIOB
#define TXB_16x2_E_Pin GPIO_PIN_8
#define TXB_16x2_E_GPIO_Port GPIOB
#define TXB_16x2_RS_Pin GPIO_PIN_9
#define TXB_16x2_RS_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
