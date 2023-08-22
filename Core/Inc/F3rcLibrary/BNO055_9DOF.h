/*
 * IMU.h
 *
 *  Created on: Aug 31, 2022
 *      Author: reiii
 */

#ifndef INC_F3RCLIBRARY_BNO055_9DOF_H_
#define INC_F3RCLIBRARY_BNO055_9DOF_H_

#include "stm32f4xx_hal.h"
#include "F3RC_LibraryParameter.h"
#include "Unit.h"
#include "BNO055_Define.h"
#include "Util.h"

enum class IMU_State{
	UNCHECK,
	READY,
	RUN
};

class BNO055_9DOF{
private:
	I2C_HandleTypeDef* hi2c;
	IMU_State state;
	F3RCLibrary::vector3 euler;
	F3RCLibrary::vector3 euler_delta;

	// ページをセットします。
	// 成功すると、trueを返します。
	bool SetPage_BNO055(uint8_t page_value){
		uint8_t hal_state;
		hal_state = HAL_I2C_Mem_Write(hi2c, BNO055_ADDR, BNO055_REG_PAGE_ID, 1, &page_value, 1, 1);
		return hal_state == HAL_OK ? true : false;
	}

	// オペレーションモードを設定します。
	// 成功すると、trueを返します。
	bool SetConfig_BNO055(uint8_t operation_value){
		uint8_t hal_state;

		if(state < IMU_State::READY) return false;

		if(!SetPage_BNO055(0)) return false;

		hal_state = HAL_I2C_Mem_Write(hi2c, BNO055_ADDR, BNO055_REG_OPR_MODE, 1, &operation_value, 1, 1);

		if(hal_state != HAL_OK) return false;

		if(operation_value == BNO055_OPERATING_CONFIG){
			HAL_Delay(19);
			state = IMU_State::READY;
		}else{
			HAL_Delay(7);
			state = IMU_State::RUN;
		}

		return true;
	}

	// 成功すると、trueを返します。
	bool ReadMem(uint16_t DevAddress, uint16_t MemAddress, uint16_t MemAddSize, uint8_t *pData, uint16_t Size){
		uint8_t hal_state;

		if(state < IMU_State::READY) return false;

		for(int i = 0; i < Size;i++){
			hal_state = HAL_I2C_Mem_Read(hi2c, DevAddress, MemAddress+i, MemAddSize, pData+i, 1, 1);
			if(hal_state != HAL_OK) return false;
		}
		return true;
	}

	// 加速度ベクトルを取得します。
	// 成功すると、vec3がセットされてtrueを返します。
	bool GetACC(F3RCLibrary::Vector3& vec3){
		uint8_t data[6];

		if(state < IMU_State::RUN) return false;

		if (!ReadMem(BNO055_ADDR, BNO055_REG_ACC_X, 1, data, 6)) return false;
		vec3.x = -(int16_t)((data[1]<<8) | data[0]) / BNO055_ACC_SCALE;
		vec3.y = -(int16_t)((data[3]<<8) | data[2]) / BNO055_ACC_SCALE;
		vec3.z = -(int16_t)((data[5]<<8) | data[4]) / BNO055_ACC_SCALE;
		return false;
	}

	// 角速度ベクトルを取得します。
	// 成功すると、vec3がセットされてtrueを返します。
	bool GetGYR(F3RCLibrary::Vector3& vec3){
		uint8_t data[6];

		if(state < IMU_State::RUN) return false;

		if (!ReadMem(BNO055_ADDR, BNO055_REG_GYR_X, 1, data, 2)) return false;
		if (!ReadMem(BNO055_ADDR, BNO055_REG_GYR_X+2, 1, data+2, 2)) return false;
		if (!ReadMem(BNO055_ADDR, BNO055_REG_GYR_X+4, 1, data+4, 2)) return false;
		vec3.x = (int16_t)((data[1]<<8) | data[0]) / BNO055_GYR_SCALE;
		vec3.y = (int16_t)((data[3]<<8) | data[2]) / BNO055_GYR_SCALE;
		vec3.z = (int16_t)((data[5]<<8) | data[4]) / BNO055_GYR_SCALE;
		return false;
	}

	// 磁気ベクトルを取得します。
	// 成功すると、vec3がセットされてtrueを返します。
	bool GetMAG(F3RCLibrary::Vector3& vec3){
		uint8_t data[6];

		if(state < IMU_State::RUN) return false;

		if (!ReadMem(BNO055_ADDR, BNO055_REG_MAG_X, 1, data, 2)) return false;
		if (!ReadMem(BNO055_ADDR, BNO055_REG_MAG_X + 2, 1, data + 2, 2)) return false;
		if (!ReadMem(BNO055_ADDR, BNO055_REG_MAG_X + 4, 1, data + 4, 2)) return false;
		vec3.x = (int16_t)((data[1]<<8) | data[0]) / BNO055_MAG_SCALE - Mag_X_Offset;
		vec3.y = (int16_t)((data[3]<<8) | data[2]) / BNO055_MAG_SCALE - Mag_Y_Offset;
		vec3.z = (int16_t)((data[5]<<8) | data[4]) / BNO055_MAG_SCALE - Mag_Z_Offset;
		return true;
	}

	//　オイラー角を取得します。
	// 成功すると、vec3がセットされてtrueを返します。
	bool GetEuler(F3RCLibrary::Vector3& vec3){
		uint8_t data[6];

		if(state < IMU_State::RUN) return false;

		if (!ReadMem(BNO055_ADDR, BNO055_REG_EUL_HEADING, 1, data, 2)) return false;
		if (!ReadMem(BNO055_ADDR, BNO055_REG_EUL_HEADING + 2, 1, data + 2, 2)) return false;
		if (!ReadMem(BNO055_ADDR, BNO055_REG_EUL_HEADING + 4, 1, data + 4, 2)) return false;
		vec3.x = (int16_t)((data[1]<<8) | data[0]) / BNO055_EULER_SCALE;
		vec3.y = (int16_t)((data[3]<<8) | data[2]) / BNO055_EULER_SCALE;
		vec3.z = (int16_t)((data[5]<<8) | data[4]) / BNO055_EULER_SCALE;
		return true;
	}

	// 四元数を返します。
	// 成功すると、quaがセットされてtrueを返します。
	bool GetQuaternion(F3RCLibrary::Quaternion& qua){
		uint8_t data[8];

		if(state < IMU_State::RUN) return false;

		if (!ReadMem(BNO055_ADDR, BNO055_REG_QUA_W, 1, data, 2)) return false;
		if (!ReadMem(BNO055_ADDR, BNO055_REG_QUA_W+2, 1, data+2, 2)) return false;
		if (!ReadMem(BNO055_ADDR, BNO055_REG_QUA_W+4, 1, data+4, 2)) return false;
		if (!ReadMem(BNO055_ADDR, BNO055_REG_QUA_W+6, 1, data+6, 2)) return false;
		qua.w = (float)(int16_t)((data[1]<<8) | data[0]) / BNO055_QUA_SCALE;
		qua.x = (float)(int16_t)((data[3]<<8) | data[2]) / BNO055_QUA_SCALE;
		qua.y = (float)(int16_t)((data[5]<<8) | data[4]) / BNO055_QUA_SCALE;
		qua.z = (float)(int16_t)((data[7]<<8) | data[6]) / BNO055_QUA_SCALE;
		return true;
	}
public:
	BNO055_9DOF(I2C_HandleTypeDef* _hi2c):
		hi2c(_hi2c), state(IMU_State::UNCHECK), euler{0.f,0.f,0.f}, euler_delta{0.f,0.f,0.f}
	{}

	/*
	 * 角度の変化量を返す関数
	 *
	 * 使わない。
	 */
	F3RCLibrary::vector3 GetAngleVelocity(){
		return euler_delta;
	}

	/*
	 * 角度Yaw,Pitch,Rollを返す関数
	 */
	F3RCLibrary::vector3 GetAngle(){
		return euler;
	}

	/*
	 * オイラー角をセンサから取得する関数
	 *
	 * 成功すれば、角度が更新される。
	 */
	void Update(){
		F3RCLibrary::vector3 _euler;
		if(!GetEuler(_euler)) return;

		float tmp_delta_X = F3RCLibrary::GetDegreeError(euler.x, _euler.x);
		float tmp_delta_Y = F3RCLibrary::GetDegreeError(euler.y, _euler.y);
		float tmp_delta_Z = F3RCLibrary::GetDegreeError(euler.z, _euler.z);

		euler_delta.x = tmp_delta_X;
		euler_delta.y = tmp_delta_Y;
		euler_delta.z = tmp_delta_Z;

		euler = _euler;
	}

	/**
	 * 開始処理を行う関数
	 *
	 * センサを確認して、オペレーティングモードを設定する。
	 * 成功時、trueを返す。
	 */
	bool Begin(uint8_t operating_mode){
		if(state != IMU_State::UNCHECK) return false;

		if(!CheckSensor()) return false;

		if(!SetConfig_BNO055(operating_mode)) return false;

		return true;
	}

	/**
	 * センサの確認を行う関数
	 *
	 * 成功時、stateをReadyに設定してtrueを返す。
	 */
	bool CheckSensor(){
		uint8_t data = 0;
		uint8_t hal_state;

		hal_state = HAL_I2C_Mem_Read(hi2c, BNO055_ADDR, BNO055_REG_CHIP_ID, 1, &data, 1, 1);

		if(hal_state != HAL_OK) return false;

		if(data != BNO055_CHIP_ID) return false;

		state = IMU_State::READY;
		return true;
	}

	/*
	 * IMUの状態を返す関数
	 *
	 * 未確認時、UNCHECK
	 * 確認時、READY
	 * 稼働時、RUN
	 */
	IMU_State GetIMUState(){
		return state;
	}
};

#endif /* INC_F3RCLIBRARY_BNO055_9DOF_H_ */
