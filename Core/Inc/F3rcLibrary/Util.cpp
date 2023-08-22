/*
 * Util.cpp
 *
 *  Created on: 2022/10/07
 *      Author: reiii
 */

#include "F3rcLibrary/Util.h"

namespace F3RCLibrary{
	/*
	 * @brief 角度差（近いほう）を返す関数
	 * @param now_yaw 基準[rad]
	 * @param target_yaw 対象[rad]
	 * @return 角度差[rad]
	 */
	float GetYawError(float now_yaw, float target_yaw){
		float yaw_error = target_yaw - now_yaw;
		yaw_error -= floorf(yaw_error / (2.0f * M_PI)) * (2.0f * M_PI);
		if(abs(yaw_error) > (float)M_PI) {
			yaw_error -= (2.0f * M_PI);
		}
		return yaw_error;
	}

	/*
	 * @brief 角度差（近いほう）を返す関数
	 * @param now_yaw 基準[deg]
	 * @param target_yaw 対象[deg]
	 * @return 角度差[deg]
	 */
	float GetDegreeError(float now_yaw, float target_yaw){
		float yaw_error = target_yaw - now_yaw;
		yaw_error -= floorf(yaw_error / (360.f)) * (360.f);
		if(abs(yaw_error) > 180.f) {
			yaw_error -= (360.f);
		}
		return yaw_error;
	}
}
