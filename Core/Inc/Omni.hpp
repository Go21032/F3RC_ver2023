/*
 * Omuni.hpp
 *
 *  Created on: 2022/11/09
 *      Author: gakuh
 */

#ifndef INC_OMNI_HPP_
#define INC_OMNI_HPP_
#include "F3rcLibrary/F3rcLibrary.h"
#include "PID.hpp"
#include "Bezier.hpp"
#include "F3rcLibrary/Util.h"
#include <math.h>

class Omni{
private:
	F3rcLibrary * f3rc;
	float r = 0.178f;


public:
	Omni(F3rcLibrary* , float t);
	float v1, v2, v3;
	PID pid_x;
	PID pid_y;
	PID pid_yaw;
	Bezier Bezier_x;
	Bezier Bezier_y;
	void IK(float x, float y, float w, float theta);
	void IK(float x, float y, float w);
	void SetV(float v1, float v2, float v3);
	void ZeroIti(float x, float y, float yaw);
	void Tuizyu(float t, float p1_x, float p2_x, float p3_x, float p4_x, float p1_y, float p2_y, float p3_y, float p4_y);

};



#endif /* INC_OMNI_HPP_ */
