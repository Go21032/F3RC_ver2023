/*
 * PID.hpp
 *
 *  Created on: 2022/10/11
 *      Author: gakuh
 */

#ifndef INC_PID_HPP_
#define INC_PID_HPP_

class PID{
	private:
		float kp;
		float ki;
		float kd;
		float integral; //積分のこと
		float past_error; //Past_errorは偏差
		float error;
		float t;

	public:
		PID(float);
		void SP(float p, float i, float d);
		float OP(float now, float goal);
};
#endif /* INC_PID_HPP_ */
