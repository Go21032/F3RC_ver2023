/*
 * F3rcLibrary.h
 *
 *  Created on: Aug 23, 2022
 *      Author: haruk
 */

#ifndef INC_F3RCLIBRARY_F3RCLIBRARY_H_
#define INC_F3RCLIBRARY_F3RCLIBRARY_H_

#include "stm32f4xx_hal.h"
#include "i2c.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"
#include "Sensor.h"
#include "AirCylinder.h"
#include "Encoder.h"
#include "Localization.h"
#include "Motor.h"
#include "Servo.h"
#include "Controller.h"
#include "Util.h"
#include "F3RC_LibraryParameter.h"

class F3rcLibrary{
private:
public:
	Sensor Sensor0, Sensor1;
	AirCylinder Air1;
	Motor M1, M2, M3, M4, M5, M6;
	Servo Servo1;
	Encoder Encoder1;
	Localization Loca;
	Controller PS3;

	F3rcLibrary() :
		Sensor0(GPIOC, GPIO_PIN_13, true),
		Sensor1(GPIOB, GPIO_PIN_12, false),
		Air1(GPIOC, GPIO_PIN_4),
		M1(&htim3, TIM_CHANNEL_1, GPIOC, GPIO_PIN_0),
		M2(&htim3, TIM_CHANNEL_2, GPIOC, GPIO_PIN_1),
		M3(&htim3, TIM_CHANNEL_3, GPIOC, GPIO_PIN_2),
		M4(&htim3, TIM_CHANNEL_4, GPIOC, GPIO_PIN_3),
		M5(&htim12, TIM_CHANNEL_1, GPIOB, GPIO_PIN_2),
		M6(&htim12, TIM_CHANNEL_2, GPIOB, GPIO_PIN_10),
		Servo1(&htim14, TIM_CHANNEL_1),
		Encoder1(&htim2, Encoder1_inverse),
		Loca(&hi2c1, &htim1, &htim8),
		PS3(&huart1)
	{}

	// 初期化後、一度呼び出してください。
	void Start(){
		M1.Begin();
		M2.Begin();
		M3.Begin();
		M4.Begin();
		M5.Begin();

		Servo1.Begin();

		// Loca.Begin() は IMUとの通信があるので、２番目に最後にすること
#ifdef LOCALIZATION_ENABLE
		HAL_Delay(100);
		Loca.Begin();
#endif
		// PS3.Begin() は ESP32との通信があるので、最後にすること
#ifdef PS3CONTROLLER_ENABLE
		//PS3.Begin();
#endif
	}
};

#endif /* INC_F3RCLIBRARY_F3RCLIBRARY_H_ */
