/*
 * PID.cpp
 *
 *  Created on: 2022/10/11
 *      Author: gakuh
 */

#include "PID.hpp"
#include <math.h>

PID::PID(float _t):kp(0), ki(0), kd(0), integral(0), past_error(0), t(_t)
{
}

/***SetParmaterの頭文字***/
void PID::SP(float p, float i, float d){
	kp = p;
	ki = i;
	kd = d;
}

/***Out Putの略***/
float PID::OP(float now, float goal){

	error = goal - now;
	float p = kp * error;
	integral += ki * (error + past_error) / 2.f * t;
	float d = kd * (error - past_error) / t;
	float u = p + integral + d;
	past_error = error;
	return u;


}
