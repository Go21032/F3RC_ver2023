/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "i2c.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"
#include "PID.hpp"
#include "Bezier.hpp"
#include "Omni.hpp"
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "F3rcLibrary/F3rcLibrary.h"
#include "F3rcLibrary/Controller.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define SECTOCNT(n) (200 * n)
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
volatile bool flag = false;
F3rcLibrary f3rc;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
enum State{
	START,
	MATU,
	MOVE_1, //ポイント１(0.5,0.5)にベジェで移動
	MOVE_2, //ポイント2(-0.7,0.5)にベジェで移動
	STAY, //(-0.7,0.5)にとどまる
	MOVE_3, //ポイント３(0,0)にベジェで移動
	END //終わり
};

enum State state = START;

float t = 0;
void changephase(enum State s);
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */


int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */


  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USART2_UART_Init();
  MX_TIM1_Init();
  MX_TIM2_Init();
  MX_TIM3_Init();
  MX_TIM8_Init();
  MX_TIM12_Init();
  MX_USART1_UART_Init();
  MX_TIM14_Init();
  MX_I2C1_Init();
  /* USER CODE BEGIN 2 */
  f3rc.Start();
  Omni oni(&f3rc, 0.005f);
/***ゼロ位置制御とか単体でやるときに使う***/
// while(1){
//	 if(f3rc.Sensor0.GetValue()){
//		 break;
//	 }
// }
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
  	if(flag){
  		//手動で足動かそう
  		//OS.IK(f3rc.PS3.GetAnalogL_X() * MOVE_XY, f3rc.PS3.GetAnalogL_Y() * MOVE_XY, f3rc.PS3.GetAnalogR_X() * MOVE_ROTATE);

//  		if(f3rc.Sensor0.GetValue()){
//  			f3rc.M2.SetDuty(-20);
//  			f3rc.M3.SetDuty(-20);
//  			f3rc.M4.SetDuty(-20);
//  		}else{
//  			f3rc.M2.SetDuty(0);
//			f3rc.M3.SetDuty(0);
//			f3rc.M4.SetDuty(0);
//  		}
  		/***ゼロ位置制御***/
  		//oni.ZeroIti(0, 0, 0);

  		/***追従***/
//		oni.Tuizyu(t, 1.0f, 1.0f, 1.0f, 1.0f);
//		t += 0.0005f;
		//tが1を超えないようにtを加算した後に判定させる
//		if(t >= 1){
//			t = 1;
//		}


  		switch(state){
  		  		case START:
  		  			if(f3rc.Sensor0.GetValue())
  		  				changephase(MATU);
  		  			break;
  		  		case MATU:
  		  			f3rc.M3.SetDuty(0);
  					f3rc.M2.SetDuty(0);
  					f3rc.M4.SetDuty(0);
  					if(t >= 100)
  						changephase(STAY_ZERO);
  					break;
  		  		case STAY_ZERO:
  		  			oni.ZeroIti(0, 0, 0);
  		  			if(f3rc.PS3.GetButton(Controller::Cross))
  		  				changephase(MOVE_1);
  		  			break;
  		  		case MOVE_1:
  		  			oni.Tuizyu(t / SECTOCNT(3.0f), 0.0f, 0.112f, 0.033f, 0.6f, 0.0f, 0.202f, 0.411f, 0.6f);
  					if(t >= SECTOCNT(3.0f))
  						changephase(MOVE_2);
  					break;
  		  		case MOVE_2:
  		  			oni.Tuizyu(t / SECTOCNT(3.0f), 0.6f, 0.346f, -0.183f, -0.5f, 0.6f, 0.778f, 0.861f, 0.6f);
  					if(t >= SECTOCNT(3.0f))
  						changephase(STAY);
  					break;
  		  		case STAY:
  					oni.ZeroIti(-0.5f, 0.6f, 0);
  					if(f3rc.PS3.GetButton(Controller::Square))
  						changephase(MOVE_3);
  					break;
  		  		case MOVE_3:
  		  			oni.Tuizyu(t / SECTOCNT(3.0f), -0.5f, -0.224f, -0.187f, 0.0f, 0.6f, 0.532f, 0.192f, 0.0f);
  		  			if(t >= SECTOCNT(3.0f))
  		  			changephase(END);
  					break;
  		  		case END:
  		  			f3rc.M3.SetDuty(0);
  					f3rc.M2.SetDuty(0);
  					f3rc.M4.SetDuty(0);
  					break;
  		  		}

				flag = false;
				t += 1; //5ms = 0.005sでtが1増加

  	}


    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 180;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 2;
  RCC_OscInitStruct.PLL.PLLR = 2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Activate the Over-Drive mode
  */
  if (HAL_PWREx_EnableOverDrive() != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

void changephase(enum State s){
	t = 0;
	state = s;
}


void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart){
	if(!(Controller::init_flag)){
		if(Controller::init_msg == (uint8_t)'A'){
			Controller::init_flag = true;
			return;
		}else{
			HAL_UART_Receive_IT(&huart1, &Controller::init_msg, 1);
			return;
		}
	}

	for(int i = 0; i < 7; i++){
		HAL_UART_Receive(&huart1, &Controller::RxData[i + 1], 1, 1);
	}
	f3rc.PS3.Update(Controller::RxData);
	HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);

	uint8_t msg = (uint8_t)'s';
	HAL_UART_Transmit(&huart1, &msg, 1, 1);
	HAL_UART_Receive_IT(&huart1, &Controller::RxData[0], 1);
}

// Interrupt by SysTick(1ms)
// 制御周??��?��? 5ms
void IntSysTick(){
	static int cnt_systick = 0;
	cnt_systick++;
	switch(cnt_systick){
	case 1:
#ifdef LOCALIZATION_ENABLE
		f3rc.Loca.Update();
#endif
		break;
	case 2:
		break;
	case 3:
		break;
	case 4:
		break;
	case 5:
		flag = true;
		cnt_systick = 0;
		break;
	}
}

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

