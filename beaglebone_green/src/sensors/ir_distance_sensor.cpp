/*
 * ir_distance_sensor.cpp
 *
 *  Created on: Jul 7, 2018
 *      Author: tudatn
 */

#include "sensors/ir_distance_sensor.h"
#include <string>
#include <sstream>
#include <unistd.h>

#include <iostream>

#define IR_AIN 		1

#define THREASHOLD	1000 //to be changed
#define TRIES		10

using namespace std;

IRDistanceSensor::IRDistanceSensor(int AINNumber)
{
	irADC = ADC(IR_AIN);
	data = irADC.readValue();
}


int IRDistanceSensor::getData()
{
	data = irADC.readValue();
	return data;
}

/*
string IRDistanceSensor::reportStatus()
{
	int activeReads = 0;

	for (int i = 0; i < TRIES; i++){
		if (getData() > THREASHOLD)
			activeReads++;
		usleep(10);
	}
	return (activeReads == TRIES) ? "active\n" : "idle\n";
}

void IRDistanceSensor::serveData()
{
	string reply;
	int bytesRead;
	while (reply.find(TERMINATE)) {
		reply = irServer->receive(&bytesRead);
		handleRequest(reply);
	}
}

void IRDistanceSensor::handleRequest(string req)
{
	cout << req << endl;
	if (req.find(DATA) == 0){
		stringstream dataStream;
		dataStream << getData() << endl;
		irServer->send(dataStream.str());
	}

	else if (req.find(STATUS) == 0){
		string status = reportStatus();
		irServer->send(status);
	}
}
*/



