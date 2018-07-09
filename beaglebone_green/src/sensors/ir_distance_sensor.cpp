/*
 * ir_distance_sensor.cpp
 *
 *  Created on: Jul 7, 2018
 *      Author: tudatn
 */

#include "sensors/ir_distance_sensor.h"

#define IR_AIN 1

IRDistanceSensor::IRDistanceSensor()
{
	//irADC = ADC(IR_AIN);
	irADC = ADC(0); // test with potentiometer
	data = irADC.readValue();
}

int IRDistanceSensor::getData()
{
	data = irADC.readValue();
	return data;
}

