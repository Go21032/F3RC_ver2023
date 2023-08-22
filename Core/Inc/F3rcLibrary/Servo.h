/*
 * Servo.h
 *
 *  Created on: Aug 23, 2022
 *      Author: haruk
 */

#ifndef INC_F3RCLIBRARY_SERVO_H_
#define INC_F3RCLIBRARY_SERVO_H_

#include "stm32f4xx_hal.h"

class Servo{
private:
	TIM_HandleTypeDef *htim;
	uint32_t channel;
	uint16_t CCR_Offset;
public:
	Servo(TIM_HandleTypeDef *_htim, uint32_t _channel) :
		htim(_htim), channel(_channel), CCR_Offset(0)
	{

	}

	// タイマーを開始します。一度呼び出してください。
	void Begin(){
		 HAL_TIM_PWM_Start(htim, channel);
	}

	// CCRの値にオフセットを追加します。
	// サーボの角度が少しズレている場合、値をセットしてください。
	// 範囲：0 ~ 59999
	// 間違った範囲の値を指定した場合、想定外の動作をする可能があります。
	void SetCCROffset(uint16_t ccr_offset){
		CCR_Offset = ccr_offset;
	}

	// サーボの角度を設定します。
	// 角度は -90度 から 90度
	void SetAngle(float angle){
		// ~2.50% ~0.50ms -90
		//  7.25%  1.45ms   0
		// 12.00%  2.40ms  90

		float duty = 0;
		// angle が -90 より小さいとき
		if(angle < -90.0f) duty = 2.5f;
		// angle が 90 より大きいとき
		if(angle > 90) duty = 12.0f;
		else{
			// 7.25 = 0度の時のDuty, 4.75 = duty / 90
			duty = 7.25 + (angle / 90.0f) * 4.75;
		}

		uint32_t ccr = (float)(duty / 100.0f * htim->Instance->ARR);
		__HAL_TIM_SET_COMPARE(htim, channel, ccr + CCR_Offset);
	}
};

#endif /* INC_F3RCLIBRARY_SERVO_H_ */
