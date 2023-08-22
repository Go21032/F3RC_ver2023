/*
 * Encoder.h
 *
 *  Created on: 2022/08/22
 *      Author: haruk
 */

#ifndef INC_F3RCLIBRARY_ENCODER_H_
#define INC_F3RCLIBRARY_ENCODER_H_

#include "stm32f4xx_hal.h"
#include "F3RC_LibraryParameter.h"

class Encoder{
private:
	TIM_HandleTypeDef *htim;
	int32_t count_total;
	int16_t count_delta;
	bool inverse;

public:
	Encoder(TIM_HandleTypeDef *_htim, bool _inv) : htim(_htim), count_total(0), count_delta(0), inverse(_inv){
		htim->Instance->CNT = 0;
	}

	// タイマーを開始します。一度呼び出してください。
	void Begin(void){
		HAL_TIM_Encoder_Start(this->htim, TIM_CHANNEL_ALL);
	}

	// 総カウント量を返す。
	int32_t GetCount(void){
		return inverse ? -this->count_total : this->count_total;
	}

	// Update 間のカウントの差を返す。
	int16_t GetCountDelta(){
		return inverse ? -this->count_delta : this->count_delta;
	}

	// CNT から値を読み出し、更新、 0 を書き込む。
	void Update(void){
		this->count_delta = htim->Instance->CNT;
		this->count_total += this->count_delta;
		htim->Instance->CNT = 0;
	}
};

#endif /* INC_F3RCLIBRARY_ENCODER_H_ */
