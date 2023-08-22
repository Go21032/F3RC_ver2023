/*
 * Controller.h
 *
 *  Created on: 2022/08/25
 *      Author: haruk
 */

#ifndef INC_F3RCLIBRARY_CONTROLLER_H_
#define INC_F3RCLIBRARY_CONTROLLER_H_

#include "stm32f4xx_hal.h"


class Controller{
private:
	UART_HandleTypeDef *huart;
	uint8_t rec_data[8];
	bool button[15][2];
	int8_t analog[6];

public:
	static uint8_t RxData[8]; 	// PS3のデータを格納
	static bool init_flag;		// ESP32から送られてくるデータが'A'かどうか判定
	static uint8_t init_msg;	// ESP32がPS3とbluetooth接続を完了した時に送信されるデータを格納

	typedef enum ButtonType{
		Cross,
		Square,
		Triangle,
		Circle,
		Up,
		Right,
		Down,
		Left,
		L1,
		R1,
		L3,
		R3,
		Select,
		Start,
		PS
	}ButtonType;

	Controller(UART_HandleTypeDef *_huart) : huart(_huart){

	}

	// ESP32とPS3の接続が完了するまで待機する関数
	// Bluetooth接続が完了するとESP32は'A'をf446reに送信する。
	// 'A'を受け取るとwhileを抜け出しESP32に's'を送信する。(通信開始)
	// 何かしら受信をするとmain.cppにあるHAL_UART_RxCpltCallback()が処理される。
	void Begin(){
		HAL_UART_Receive_IT(huart, &init_msg, 1);
		while(1){
			if(init_flag)
				break;
		}
		uint8_t msg = (uint8_t)'s';
		HAL_UART_Transmit(huart, &msg, 1, 1);
		HAL_UART_Receive_IT(huart, &RxData[0], 1);
	}

	// 左アナログスティックのX軸
	// -1 ~ 1 の範囲
	float GetAnalogL_X(){
		return analog[0] / 128.f;
	}

	// 左アナログスティックのY軸
	// -1 ~ 1 の範囲
	float GetAnalogL_Y(){
		return -analog[1] / 128.f;
	}

	// 右アナログスティックのX軸
	// -1 ~ 1 の範囲
	float GetAnalogR_X(){
		return analog[2] / 128.f;
	}

	// 右アナログスティックのY軸
	// -1 ~ 1 の範囲
	float GetAnalogR_Y(){
		return -analog[3] / 128.f;
	}

	// R2トリガの軸
	// -1 ~ 1 の範囲
	float GetAnalogR2(){
		return (uint8_t)analog[4] / 255.f;
	}

	// L2トリガの軸
	// -1 ~ 1 の範囲
	float GetAnalogL2(){
		return (uint8_t)analog[5] / 255.f;
	}

	bool GetButton(ButtonType bt){
		return button[bt][0];
	}

	void Update(uint8_t *new_data){
		for(int i = 0; i < 14; i++){
			button[i][1] = button[i][0];
		}

		for(int i = 0; i < 8; i++){
			button[i][0] = (bool)((*new_data >> i) & 0x1);
		}

		for(int i = 8; i < 15; i++){
			button[i][0] = (bool)((*(new_data + 1) >> (i - 8)) & 0x1);
		}

		for(int i = 0; i < 6; i++){
			analog[i] = *(new_data + i + 2);
		}
	}

};

#endif /* INC_F3RCLIBRARY_CONTROLLER_H_ */
