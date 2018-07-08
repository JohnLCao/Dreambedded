/*
 * monitor.cpp
 *
 *  Created on: Jun 25, 2018
 *       Notes:
 */

#include "monitor/monitor.h"
#include <iostream>

bool Monitor::setActuator(Actuator act, bool set)
{
	//TODO - function signature may need to change
	ADC IRSensor = ADC(1);
	cout << IRSensor.readValue() << endl;
	return false;
}

int main()
{
	Monitor::setActuator();
	std::cout << "test" << std::endl;
	return 0;
}
