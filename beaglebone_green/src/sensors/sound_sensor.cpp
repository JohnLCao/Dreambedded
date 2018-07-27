/*
 * ir_distance_sensor.cpp
 *
 *  Created on: Jul 7, 2018
 *      Author: tudatn
 */

#include "sensors/sound_sensor.h"
#include <string>
#include <sstream>
#include <unistd.h>

#include <iostream>

using namespace std;

SoundSensor::SoundSensor()
{
	soundAIN = 4; // default AIN4 P9_GPIO33
	soundADC = ADC(soundAIN);
}

SoundSensor::~SoundSensor() {

}

SoundSensor::SoundSensor(int AINNumber)
{
	soundAIN = AINNumber;
	soundADC = ADC(soundAIN);
}

int SoundSensor::getData()
{
	data = soundADC.readValue();
	return data;
}
