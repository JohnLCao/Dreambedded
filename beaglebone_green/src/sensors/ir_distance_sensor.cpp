/*
 * ir_distance_sensor.cpp
 *
 *  Created on: Jul 7, 2018
 *      Author: tudatn
 */

#include "sensors/ir_distance_sensor.h"
#include <string>
#include <sstream>

#define IR_AIN 		1
#define UDP_PORT 	12345
#define TERMINATE 	"stop\n"
#define GET_DATA	"data\n"

using namespace std;

IRDistanceSensor::IRDistanceSensor()
{
	irADC = ADC(0); // test with potentiometer
	//irADC = ADC(IR_AIN);
	irServer = new UdpServer(UDP_PORT);
	data = irADC.readValue();
}

IRDistanceSensor::~IRDistanceSensor()
{
	delete irServer;
}

int IRDistanceSensor::getData()
{
	data = irADC.readValue();
	return data;
}

void IRDistanceSensor::serveData()
{
	string reply;
	int bytesRead;
	while (reply.compare(TERMINATE)) {
		reply = irServer->receive(&bytesRead);
		handleRequest(reply);
	}
}

void IRDistanceSensor::handleRequest(string req)
{
	if (req.compare(GET_DATA) == 0){
		stringstream dataStream;
		dataStream << getData() << "\n";
		irServer->send(dataStream.str());
	}
}




