/*
 * Controller.cpp
 *
 *  Created on: 2022/10/07
 *      Author: haruk
 */

#include "Controller.h"

uint8_t Controller::RxData[8] = {0};
bool Controller::init_flag = false;
uint8_t Controller::init_msg = 0;

