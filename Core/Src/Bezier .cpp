/*
 * Bezier .cpp
 *
 *  Created on: 2022/10/17
 *      Author: gakuh
 */

#include "Bezier.hpp"

Bezier::Bezier()
{
}

/**
 * 初期値p1からp2の点までを線形補間する
 * (1-t)p1+t*p2
 */
float Bezier::Bezier1(float t, float p1, float p2)
{
    return (1.f - t) * p1 + t * p2;
}

/**
 * 前のやつからp3の点までを線形補間する
 */
float Bezier::Bezier2(float t, float p1, float p2, float p3)
{
    return Bezier1(t, Bezier1(t, p1, p2), Bezier1(t, p2, p3));
}

float Bezier::Bezier3(float t, float p1, float p2, float p3, float p4)
{
    return Bezier1(t, Bezier2(t, p1, p2, p3), Bezier2(t, p2, p3, p4));
}

float Bezier::Bezier4(float t, float p1, float p2, float p3, float p4, float p5)
{
    return Bezier1(t, Bezier3(t, p1, p2, p3, p4), Bezier3(t, p2, p3, p4, p5));
}

float Bezier::Bezier5(float t, float p1, float p2, float p3, float p4, float p5, float p6)
{
    return Bezier1(t, Bezier4(t, p1, p2, p3, p4, p5), Bezier4(t, p2, p3, p4, p5, p6));
}

float Bezier::Bezier6(float t, float p1, float p2, float p3, float p4, float p5, float p6, float p7)
{
    return Bezier1(t, Bezier5(t, p1, p2, p3, p4, p5, p6), Bezier5(t, p2, p3, p4, p5, p6, p7));
}
