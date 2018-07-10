/*
 * monitor.cpp
 *
 *  Created on: Jun 25, 2018
 *       Notes:
 */

#include "monitor/monitor.h"

using namespace std;

//XXX add #define _GLIBCXX_USE_CXX11_ABI 0  	--as a stop gap.
// 		  before including any C++ libraries.

int main()
{
	IRDistanceSensor irSensor = IRDistanceSensor();
	while (true){
		cout << "IR distance value: " << irSensor.getData() << endl;
	}
	return 0;
}
