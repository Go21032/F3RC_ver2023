/*
 * Sensor.h
 *
 *  Created on: 2022/08/21
 *      Author: haruk
 */

#ifndef INC_SENSOR_H_
#define INC_SENSOR_H_

#include "stm32f4xx_hal.h"

class Sensor{
private:
	GPIO_TypeDef *pinType;
	uint16_t pinNum;
	int value = 0;
	bool inverse;

public:
	Sensor(GPIO_TypeDef *_type, uint16_t _num, bool _inverse){
		this->pinType = _type;
		this->pinNum = _num;
		this->inverse = _inverse;
	}

	bool GetValue(void){
		value = (bool)HAL_GPIO_ReadPin(this->pinType, this->pinNum);
		return inverse ? !value : value;
	}
};

#endif /* INC_SENSOR_H_ */
