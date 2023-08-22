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
extern void IntSysTick();
/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define B1_Pin GPIO_PIN_13
#define B1_GPIO_Port GPIOC
#define MD_DIR_1_Pin GPIO_PIN_0
#define MD_DIR_1_GPIO_Port GPIOC
#define MD_DIR_2_Pin GPIO_PIN_1
#define MD_DIR_2_GPIO_Port GPIOC
#define MD_DIR_3_Pin GPIO_PIN_2
#define MD_DIR_3_GPIO_Port GPIOC
#define MD_DIR_4_Pin GPIO_PIN_3
#define MD_DIR_4_GPIO_Port GPIOC
#define USART_TX_Pin GPIO_PIN_2
#define USART_TX_GPIO_Port GPIOA
#define USART_RX_Pin GPIO_PIN_3
#define USART_RX_GPIO_Port GPIOA
#define LD2_Pin GPIO_PIN_5
#define LD2_GPIO_Port GPIOA
#define MD_PWM_1_Pin GPIO_PIN_6
#define MD_PWM_1_GPIO_Port GPIOA
#define Servo_PWM1_Pin GPIO_PIN_7
#define Servo_PWM1_GPIO_Port GPIOA
#define GPIO_Solenoid1_Pin GPIO_PIN_4
#define GPIO_Solenoid1_GPIO_Port GPIOC
#define GPIO_Solenoid2_Pin GPIO_PIN_5
#define GPIO_Solenoid2_GPIO_Port GPIOC
#define MD_PWM_3_Pin GPIO_PIN_0
#define MD_PWM_3_GPIO_Port GPIOB
#define MD_PWM_4_Pin GPIO_PIN_1
#define MD_PWM_4_GPIO_Port GPIOB
#define MD_DIR_5_Pin GPIO_PIN_2
#define MD_DIR_5_GPIO_Port GPIOB
#define MD_DIR_6_Pin GPIO_PIN_10
#define MD_DIR_6_GPIO_Port GPIOB
#define MD_PWM_5_Pin GPIO_PIN_14
#define MD_PWM_5_GPIO_Port GPIOB
#define MD_PWM_6_Pin GPIO_PIN_15
#define MD_PWM_6_GPIO_Port GPIOB
#define ENCODER_Y_A_Pin GPIO_PIN_6
#define ENCODER_Y_A_GPIO_Port GPIOC
#define ENCODER_Y_B_Pin GPIO_PIN_7
#define ENCODER_Y_B_GPIO_Port GPIOC
#define ENCODER_X_A_Pin GPIO_PIN_8
#define ENCODER_X_A_GPIO_Port GPIOA
#define ENCODER_X_B_Pin GPIO_PIN_9
#define ENCODER_X_B_GPIO_Port GPIOA
#define ESP32_RX_Pin GPIO_PIN_10
#define ESP32_RX_GPIO_Port GPIOA
#define TMS_Pin GPIO_PIN_13
#define TMS_GPIO_Port GPIOA
#define TCK_Pin GPIO_PIN_14
#define TCK_GPIO_Port GPIOA
#define ENCODER_1_A_Pin GPIO_PIN_15
#define ENCODER_1_A_GPIO_Port GPIOA
#define SWO_Pin GPIO_PIN_3
#define SWO_GPIO_Port GPIOB
#define MD_PWM_2_Pin GPIO_PIN_5
#define MD_PWM_2_GPIO_Port GPIOB
#define ESP32_TX_Pin GPIO_PIN_6
#define ESP32_TX_GPIO_Port GPIOB
#define ENCODER_1_B_Pin GPIO_PIN_9
#define ENCODER_1_B_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
