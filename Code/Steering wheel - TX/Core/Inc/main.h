/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
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
#include "stm32f4xx_hal.h"

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

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

extern int __io_putchar(int ch);


/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define SPI2_LATCH_Pin GPIO_PIN_2
#define SPI2_LATCH_GPIO_Port GPIOC
#define USART_TX_Pin GPIO_PIN_2
#define USART_TX_GPIO_Port GPIOA
#define USART_RX_Pin GPIO_PIN_3
#define USART_RX_GPIO_Port GPIOA
#define TL_Pin GPIO_PIN_5
#define TL_GPIO_Port GPIOC
#define BS_Pin GPIO_PIN_12
#define BS_GPIO_Port GPIOB
#define BS_EXTI_IRQn EXTI15_10_IRQn
#define BB_Pin GPIO_PIN_13
#define BB_GPIO_Port GPIOB
#define BB_EXTI_IRQn EXTI15_10_IRQn
#define BL_Pin GPIO_PIN_14
#define BL_GPIO_Port GPIOB
#define BL_EXTI_IRQn EXTI15_10_IRQn
#define BR_Pin GPIO_PIN_15
#define BR_GPIO_Port GPIOB
#define BR_EXTI_IRQn EXTI15_10_IRQn
#define DE_Pin GPIO_PIN_6
#define DE_GPIO_Port GPIOC
#define NRF24_CSN_Pin GPIO_PIN_7
#define NRF24_CSN_GPIO_Port GPIOC
#define TR_Pin GPIO_PIN_8
#define TR_GPIO_Port GPIOC
#define BE_Pin GPIO_PIN_9
#define BE_GPIO_Port GPIOC
#define BE_EXTI_IRQn EXTI9_5_IRQn
#define DG_Pin GPIO_PIN_10
#define DG_GPIO_Port GPIOA
#define TMS_Pin GPIO_PIN_13
#define TMS_GPIO_Port GPIOA
#define TCK_Pin GPIO_PIN_14
#define TCK_GPIO_Port GPIOA
#define SWO_Pin GPIO_PIN_3
#define SWO_GPIO_Port GPIOB
#define DY_Pin GPIO_PIN_4
#define DY_GPIO_Port GPIOB
#define DR_Pin GPIO_PIN_5
#define DR_GPIO_Port GPIOB
#define NRF24_CE_Pin GPIO_PIN_6
#define NRF24_CE_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */


/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
