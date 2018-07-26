/*
 * sound_sensor.h
 *
 *  Created on: Jul 25, 2018
 *      Author: tudatn
 */

#ifndef HEADER_SENSORS_SOUND_SENSOR_H_
#define HEADER_SENSORS_SOUND_SENSOR_H_

#include "sensor.h"
#include "support/adc.h"
#include "support/network/network.h"
#include <string>

class SoundSensor : public Sensor {
public:
	SoundSensor();
	SoundSensor(int AINNumber);
	~SoundSensor();
	int getData();
private:
	int soundAIN;
	int data;
	ADC soundADC;
};

#endif /* HEADER_SENSORS_SOUND_SENSOR_H_ */
