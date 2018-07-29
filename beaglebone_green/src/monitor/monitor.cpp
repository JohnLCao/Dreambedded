/*
 * monitor.cpp
 *
 *  Created on: Jun 25, 2018
 *       Notes:
 */

#include "monitor/monitor.h"
#include <iostream>
#include <thread>
#include <cstdlib>
#include <ratio>
#include <chrono>
#include <unistd.h>
#include "support/network/network.h"
#include "support/network/udp_server.h"
#include "sensors/sound_sensor.h"
#include "sensors/ir_distance_sensor.h"
#include "support/gpio.h"

#define POLL_PERIOD 			100000
#define TIME_INTERVAL_ms 		500
#define SOUND_TRIGGER_VALUE 	1200
#define IR_TRIGGER_VALUE 		1000
#define IR_SLEEP_MICROSECONDS 	10000
#define NUM_SAMPLES 			10
#define NUM_SLAPS 				2
#define SOUND_SENSOR_AIN 		4
#define IR_SENSOR_AIN	 		1
#define STOP 					"stop"
#define STATUS 					"status"
#define ACTIVE					"active"
#define IDLE					"idle"
#define PORT					12345

typedef std::chrono::high_resolution_clock Time;
typedef std::chrono::milliseconds ms;
typedef std::chrono::duration<float> fsec;

using namespace std;

//XXX add #define _GLIBCXX_USE_CXX11_ABI 0  	--as a stop gap.
// 		  before including any C++ libraries.

// status for sensors
bool soundRelayActivation = false;
bool irRelayActivation = false;

// function for soundSensor thread
// This function counts the number
void driveByClappingWithSoundSensor() {
	auto begin = Time::now();
	int soundReadValue = 0;
	int slapCount = 0;
	int reachTriggerValue = 0;
	int normalReadingValue = 0;

	SoundSensor soundSensor = SoundSensor();

	while (1) {
		slapCount = 0;
        while (slapCount <= NUM_SLAPS) {
            reachTriggerValue = 0;
			normalReadingValue = 0;
            for (int i = 0; i < NUM_SAMPLES; i++) {
                soundReadValue = soundSensor.getData();
				normalReadingValue += soundReadValue;
                if (soundReadValue > SOUND_TRIGGER_VALUE) {
					// std::cout << "soundReadValue: " << soundReadValue << '\n';
                    reachTriggerValue = 1;
                }
            }

			while (reachTriggerValue && soundSensor.getData() > (normalReadingValue / NUM_SAMPLES)) {
				// keeping reading
			}

            if (reachTriggerValue) {
                slapCount++;
                if (slapCount == 1) begin = Time::now();
                if (slapCount == 2) {
                    auto end = Time::now();
                    fsec fs = end - begin;
                    ms elapse = std::chrono::duration_cast<ms>(fs);
                    if (elapse.count() < TIME_INTERVAL_ms ) {
						soundRelayActivation = !soundRelayActivation;
                        break;
                    } else {
                        // reset slapCount to 1
                        slapCount = 1;
                        begin = end;
                    }
                }
            }
        }
    }
}

void driveByThresholdWithIRSensor()
{
	int irReadValue = 0;
	int triggerTimes = 0;

	IRDistanceSensor irSensor = IRDistanceSensor();
	while (1) {
		for (int i = 0; i < NUM_SAMPLES; i++){
			triggerTimes = 0;
			irReadValue = irSensor.getData();
			if (irReadValue > IR_TRIGGER_VALUE){
				triggerTimes++;
				usleep(IR_SLEEP_MICROSECONDS);
			} else {
				break;
			}
		}
		//IR sensor will turn light off if no one is in the room
		irRelayActivation = (triggerTimes == NUM_SAMPLES);
	}
}

bool BBG_network_cb(Network* net)
{
	int bytesRead;
	UdpServer* udp = net->getServer();
  	string reply = udp->receive(&bytesRead);
  	if (reply.find(STATUS) == 0){
  		string res = (soundRelayActivation || irRelayActivation) ? ACTIVE : IDLE;
  		udp->send(res);
  		return true;
  	}
  	//exit if received stop command
  	return reply.find(STOP) != 0;
}

int main()
{
	cout << "MAIN <------" << endl;

	// start soundSensor thread
	thread soundSensor(driveByClappingWithSoundSensor);
	// start IR sensor thread
	thread irSensor (driveByThresholdWithIRSensor);

	Network monitor(PORT, &BBG_network_cb);
	monitor.wait();

	// Join threads
	soundSensor.join();
	irSensor.join();

	return 0;
}
