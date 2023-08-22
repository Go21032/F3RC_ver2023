/*
 * Motor.h
 *
 *  Created on: 2022/08/21
 *      Author: haruk
 */

#ifndef INC_F3RCLIBRARY_MOTOR_H_
#define INC_F3RCLIBRARY_MOTOR_H_

#include "stm32f4xx_hal.h"
#include "math.h"

class Motor{
private:
	TIM_HandleTypeDef *htim;
	uint32_t channel;
	GPIO_TypeDef *pinType;
	uint16_t pinNum;
	uint32_t ccr;
	float dutyLimit = 100.f;

public:
	Motor(TIM_HandleTypeDef *_htim, uint32_t _channel, GPIO_TypeDef *_pinType, uint16_t _pinNum) : htim(_htim), channel(_channel), pinType(_pinType), pinNum(_pinNum){

	}

	// タイマーを開始します。一度呼び出してください。
	void Begin(){
		HAL_TIM_PWM_Start(htim, channel);
		__HAL_TIM_SET_COMPARE(htim, channel, 0);
	}

	// PWM の Duty比 を変更します。
	// 値の範囲：-100.0f ~ 100.0f
	void SetDuty(float duty){
//		HAL_TIM_PWM_Stop(htim, channel); <- 諸悪の根源
		if(duty < 0){
			HAL_GPIO_WritePin(pinType, pinNum, GPIO_PIN_SET);
//			duty = (-duty) < dutyLimit ? -duty : dutyLimit;
		}else{
			HAL_GPIO_WritePin(pinType, pinNum, GPIO_PIN_RESET);
		}
		duty = abs(duty) < dutyLimit ? abs(duty): dutyLimit;
		ccr = htim->Instance->ARR * duty / 100.f;
		__HAL_TIM_SET_COMPARE(htim, channel, ccr);
	}

//	uint32_t GetAAR(){
//		return htim->Instance->ARR;
//	}
};

#endif /* INC_F3RCLIBRARY_MOTOR_H_ */
