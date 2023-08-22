/*
 * Unit.h
 *
 *  Created on: Aug 31, 2022
 *      Author: reiii
 */

#ifndef INC_F3RCLIBRARY_UNIT_H_
#define INC_F3RCLIBRARY_UNIT_H_

#include <math.h>

#define RAD_2_DEG		(180.0f / M_PI)
#define DEG_2_RAD		(M_PI / 180.0f)

// 単位系を追加する。
namespace F3RCLibrary{
	typedef struct vector3{
		float x;
		float y;
		float z;
	}Vector3;
	typedef struct quaternion{
		float x;
		float y;
		float z;
		float w;
	}Quaternion;
	typedef Quaternion Vector4;
}

#endif /* INC_F3RCLIBRARY_UNIT_H_ */
