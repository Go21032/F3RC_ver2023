/*
 * PR.hpp
 *
 *  Created on: 2022/10/29
 *      Author: gakuh
 */

#ifndef INC_PR_HPP_
#define INC_PR_HPP_


#define MOVE_XY 30.f
#define MOVE_ROTATE 10.f
/**メカナムのパラメーター
 * メカナムホイールのローラ角度 φ = 45度
 * ホイールベース a = 21cm = 0.21m
 * トレット b = 0.34m
 * α = 45 - arctan0.21/0.34 = 13.3
 * L = √{(0.21)^2+(0.34)^2} * cos13.3 = 0.3889 =0.39
 */
#define φ 45
//#define φ 0.785
#define L 0.39

#endif /* INC_PR_HPP_ */
