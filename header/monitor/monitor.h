/*
 * monitor.h
 *
 *  Created on: Jun 22, 2018
 *  	 Notes: 
 */

#ifndef __MONITOR_H__   
#define __MONITOR_H__

#include "sensors/sensor.h"
#include "actuators/actuator.h"

class Monitor 
{
	private:
	public:
		bool setActuator(Actuator act, bool set);	
	//TODO: complete interface	
};

#endif
