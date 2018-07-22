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
#include "support/network.h"

class IRDistanceSensor : public Sensor {
public:
	IRDistanceSensor();
	~IRDistanceSensor();
	void serveData();
private:
	int data;
	ADC irADC;
	UdpServer* irServer;
	int getData();
	void handleRequest(string req);
};

#endif /* HEADER_SENSORS_IR_DISTANCE_SENSOR_H_ */
