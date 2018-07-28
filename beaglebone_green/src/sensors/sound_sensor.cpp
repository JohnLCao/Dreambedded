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
#define SOUND_AIN 4 // default AIN4 P9_GPIO33

using namespace std;

SoundSensor::SoundSensor()
{
	soundAIN = SOUND_AIN;
	soundADC = ADC(soundAIN);
}

SoundSensor::SoundSensor(int AINNumber)
{
	soundAIN = AINNumber;
	soundADC = ADC(soundAIN);
}

SoundSensor::~SoundSensor(){}

int SoundSensor::getData()
{
	data = soundADC.readValue();
	return data;
}
