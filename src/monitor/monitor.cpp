/*
 * monitor.cpp
 *
 *  Created on: Jun 25, 2018
 *       Notes:
 */

#include "monitor/monitor.h"
#include <iostream>

using namespace std;

int main()
{
	IRDistanceSensor irSensor = IRDistanceSensor();
	while (true){
		cout << "IR distance value: " << irSensor.getData() << endl;
	}
	return 0;
}
