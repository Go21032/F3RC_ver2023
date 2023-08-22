/*
 * Localization.h
 *
 *  Created on: Aug 23, 2022
 *      Author: haruk
 */

#ifndef INC_F3RCLIBRARY_LOCALIZATION_H_
#define INC_F3RCLIBRARY_LOCALIZATION_H_

#include <math.h>
#include "stm32f4xx_hal.h"
#include "F3RC_LibraryParameter.h"
#include "Unit.h"
#include "Encoder.h"
#include "BNO055_9DOF.h"

class Localization{
private:
	BNO055_9DOF imu;
	Encoder encoder_X, encoder_Y;
	float tmp_odd_x;
	float tmp_odd_y;
	float offsetX;
	float offsetY;
	float odd_x;
	float odd_y;
	float odd_yaw;

public:
	Localization(I2C_HandleTypeDef* _i2c_imu, TIM_HandleTypeDef* _tim_encx, TIM_HandleTypeDef* _tim_ency) : imu(_i2c_imu), encoder_X(_tim_encx, EncoderX_inverse), encoder_Y(_tim_ency, EncoderY_inverse), offsetX(Initial_Position_X), offsetY(Initial_Position_Y), odd_x(0.f), odd_y(0.f), odd_yaw(0.f){

	}

	// いろいろ初期化後一度のみ実行してください。
	void Begin(){
		encoder_X.Begin();
		encoder_Y.Begin();

		if(Using_IMU){
			if(imu.Begin(BNO055_OperationMode)){
				// チカ
				HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
				HAL_Delay(100);
				HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
				HAL_Delay(100);
			}else{
				// チカっとチカ千花っ♡
				HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
				HAL_Delay(100);
				HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
				HAL_Delay(100);
				HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
				HAL_Delay(100);
				HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
				HAL_Delay(100);
			}
		}
	}

	// 現在の場所 X [m]
	float GetX(){
		return odd_x + offsetX;
	}

	// 現在の場所 Y [m]
	float GetY(){
		return odd_y + offsetY;
	}

	// 現在の角度 Yaw [rad]
	float GetYaw(){
		return odd_yaw;
	}

	// 定期実行してください。
	void Update(){
		encoder_X.Update();
		encoder_Y.Update();

		if(Using_IMU)
			imu.Update();

		// temp delta Velocity X [m]
		float tmp_velocity_X = (encoder_X.GetCountDelta() / EncoderX_PPR) * (EncoderX_Diameter * M_PI);
		// temp delta Velocity Y [m]
		float tmp_velocity_Y = (encoder_Y.GetCountDelta() / EncoderY_PPR) * (EncoderY_Diameter * M_PI);

		tmp_velocity_X += imu.GetAngleVelocity().x * DEG_2_RAD * EncoderX_YOffset;
		tmp_velocity_Y += imu.GetAngleVelocity().x * DEG_2_RAD * EncoderY_XOffset;

		// Velocity Yaw [rad]
		odd_yaw = -imu.GetAngle().x * DEG_2_RAD;

		// delta Velocity X
		float velocity_X = tmp_velocity_X * cosf(odd_yaw) - tmp_velocity_Y * sinf(odd_yaw);
		// delta Velocity Y
		float velocity_Y = tmp_velocity_X * sinf(odd_yaw) + tmp_velocity_Y * cosf(odd_yaw);

		tmp_odd_x += velocity_X;
		tmp_odd_y += velocity_Y;

		odd_x = tmp_odd_x;// + EncoderY_XOffset * cosf(odd_yaw) - EncoderX_YOffset * sinf(odd_yaw) - EncoderY_XOffset;
		odd_y = tmp_odd_y;// + EncoderY_XOffset * sinf(odd_yaw) + EncoderX_YOffset * cosf(odd_yaw) - EncoderX_YOffset;
	}
};

#endif /* INC_F3RCLIBRARY_LOCALIZATION_H_ */
