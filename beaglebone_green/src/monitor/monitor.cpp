/*
 * monitor.cpp
 *
 *  Created on: Jun 25, 2018
 *       Notes:
 */

#include "monitor/monitor.h"
#include <string>
#include <iostream>
#include "support/network.h"

#define POLL_PERIOD 100000

using namespace std;

//XXX add #define _GLIBCXX_USE_CXX11_ABI 0  	--as a stop gap.
// 		  before including any C++ libraries.

int main()
{
	IRDistanceSensor irSensor = IRDistanceSensor();
//
//	//TODO: this should be moved to the main() / binary for the irSensor.
	irSensor.serveData();
	return 0;
}
