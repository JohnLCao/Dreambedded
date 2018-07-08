/*
 * ir_distance_sensor.cpp
 *
 *  Created on: Jul 7, 2018
 *      Author: tudatn
 */

#include "ir_distance_sensor.h"

#define IR_AIN 1

IRDistanceSensor::IRDistanceSensor() {
	// TODO : import ADC file
	irADC = ADC(IR_AIN);
}






