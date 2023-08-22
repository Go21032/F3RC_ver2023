/*
 * Omuni.cpp
 *
 *  Created on: 2022/11/09
 *      Author: gakuh
 */
#include "Omni.hpp"

Omni::Omni(F3rcLibrary * f3rc, float t):r(0.178f), pid_x(t), pid_y(t), pid_yaw(t)
{
    this->f3rc = f3rc;
    /***PIDのゲインの設定***/
    pid_x.SP(500.f, 0.f, 0.01f);
    pid_y.SP(500.f, 0.f, 0.01f);
    pid_yaw.SP(700.f, 0.f, 0.01f);

}

/***フィールド座標***/
void Omni::IK(float x, float y, float w, float theta)
{
	v1 = x * cosf(theta) + y * sinf(theta) + r * w;
	v2 = x * cosf(theta + 2.0f/3.0f * M_PI)+ y * sinf(theta + 2.0f/3.0f * M_PI) + r * w;
	v3 = x * cosf(theta + 4.0f/3.0f * M_PI) + y * sinf(theta + 4.0f/3.0f * M_PI) + r * w;
}

/***IKは逆運動学のことです***/
/***機体座標***/
/***機体座標でthetaを0にすればフィールド座標と一致になる。なぜなら、機体が傾いていないから***/
void Omni::IK(float x, float y, float w)
{
	IK(x, y, w, 0);
}

void Omni::SetV(float v1, float v2, float v3){
	f3rc->M3.SetDuty(-v1);
	f3rc->M2.SetDuty(-v2);
	f3rc->M4.SetDuty(-v3);
}

/***ゼロ位置制御***/
void Omni::ZeroIti(float x, float y, float yaw){

	float now_x, now_y, now_yaw;
	now_x = f3rc->Loca.GetX();
	now_y = f3rc->Loca.GetY();

	float goal_x, goal_y, goal_yaw;
	goal_x = x;
	goal_y = y;

	float out_x, out_y, out_yaw;
	out_x = pid_x.OP(now_x, goal_x);
	out_y = pid_y.OP(now_y, goal_y);
	out_yaw = pid_yaw.OP(F3RCLibrary::GetYawError(-f3rc->Loca.GetYaw(), 0), 0.0f);

	IK(out_x, out_y, out_yaw, now_yaw);

	SetV(v1, v2, v3);
}

/***経路追従***/
void Omni::Tuizyu(float t, float p1_x, float p2_x, float p3_x, float p4_x, float p1_y, float p2_y, float p3_y, float p4_y){
	float goal_x, goal_y;
	goal_x = Bezier_x.Bezier3(t, p1_x, p2_x, p3_x, p4_x);
	goal_y = Bezier_y.Bezier3(t, p1_y, p2_y, p3_y, p4_y);
	ZeroIti(goal_x, goal_y, 0);
}
