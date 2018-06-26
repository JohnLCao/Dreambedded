/*
 * monitor.h
 *
 *  Created on: Jun 22, 2018
 *  	 Notes: 
 */

#ifndef __MONITOR_H__   
#define __MONITOR_H__

#include "header/sensors/sensor.h"
#include "header/actuators/actuator.h"

class Monitor 
{
	private:
	public:
		bool setActuator(Actuator act, bool set);	
	//TODO: complete interface	
};

#endif
