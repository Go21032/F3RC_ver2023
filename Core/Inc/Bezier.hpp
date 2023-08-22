/*
 * Bezier.hpp
 *
 *  Created on: 2022/10/17
 *      Author: gakuh
 */

#ifndef INC_BEZIER_HPP_
#define INC_BEZIER_HPP_
class Bezier {
    public:
        Bezier();
        float Bezier1(float t, float p1, float p2);
        float Bezier2(float t, float p1, float p2, float p3);
        float Bezier3(float t, float p1, float p2, float p3, float p4);
        float Bezier4(float t, float p1, float p2, float p3, float p4, float p5);
        float Bezier5(float t, float p1, float p2, float p3, float p4, float p5, float p6);
        float Bezier6(float t, float p1, float p2, float p3, float p4, float p5, float p6, float p7);
};


#endif /* INC_BEZIER_HPP_ */
