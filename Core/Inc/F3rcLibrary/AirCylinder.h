/*
 * AirCylinder.h
 *
 *  Created on: 2022/08/22
 *      Author: haruk
 */

#ifndef INC_F3RCLIBRARY_AIRCYLINDER_H_
#define INC_F3RCLIBRARY_AIRCYLINDER_H_

#include "stm32f4xx_hal.h"

class AirCylinder{
private:
	GPIO_TypeDef *pinType;
	uint16_t pinNum;

public:
	AirCylinder(GPIO_TypeDef *_pinType, uint16_t _pinNum) : pinType(_pinType), pinNum(_pinNum){

	}

	// ソレノイドをON
	void Open(void){
		HAL_GPIO_WritePin(pinType, pinNum, GPIO_PIN_SET);
	}

	// ソレノイドをOFF
	void Close(void){
		HAL_GPIO_WritePin(pinType, pinNum, GPIO_PIN_RESET);
	}
};

#endif /* INC_F3RCLIBRARY_AIRCYLINDER_H_ */
