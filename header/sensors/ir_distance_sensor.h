/*
 * ir_distance_sensor.h
 *
 *  Created on: Jul 7, 2018
 *      Author: tudatn
 */

#ifndef HEADER_SENSORS_IR_DISTANCE_SENSOR_H_
#define HEADER_SENSORS_IR_DISTANCE_SENSOR_H_

#include "sensor.h"
#include "support/adc.h"

class IRDistanceSensor : public Sensor {
public:
	IRDistanceSensor();
	int getData();
private:
	int data;
	ADC irADC;
};

#endif /* HEADER_SENSORS_IR_DISTANCE_SENSOR_H_ */
