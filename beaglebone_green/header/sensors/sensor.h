/*
 * sensor.h
 *
 *  Created on: Jun 22, 2018
 *  	 Notes: 
 */

#ifndef __SENSOR_H__   
#define __SENSOR_H__

class Sensor
{
	private: 
	public:
		Sensor();
		virtual int getData() = 0;
		virtual ~Sensor();
};

//resolve undefined references in sub classes
inline Sensor::Sensor(){};
inline Sensor::~Sensor(){};

#endif
