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
#define TIME_INTERVAL_ms 		700
#define SOUND_TRIGGER_VALUE 	1200
#define IR_TRIGGER_VALUE 		1600
#define IR_SLEEP_MICROSECONDS 	10000
#define NUM_SAMPLES 			10
#define NUM_SLAPS 				2
#define SOUND_SENSOR_AIN 		4
#define IR_SENSOR_AIN	 		1
#define STOP 					"stop"
#define STATUS 					"status"
#define ACTIVE					"active"
#define IDLE					"idle"
#define PORT					2
#define IR_ON_MSG  				"ir:on"
#define IR_OFF_MSG				"ir:off"
#define SOUND_ON_MSG			"sound:on"
#define SOUND_OFF_MSG			"sound:off"

#define RPI_IP 					"142.58.82.120"

typedef std::chrono::high_resolution_clock Time;
typedef std::chrono::milliseconds ms;
typedef std::chrono::duration<float> fsec;

using namespace std;

//XXX add #define _GLIBCXX_USE_CXX11_ABI 0  	--as a stop gap.
// 		  before including any C++ libraries.

// status for sensors
bool soundRelayActivation = false;
bool irRelayActivation = false;
string soundState = IR_ON_MSG;

// function for soundSensor thread
// This function counts the number
void driveByClappingWithSoundSensor() {
	auto begin = Time::now();
	int slapCount = 0;

	SoundSensor soundSensor = SoundSensor();
	int soundReadValue = 0;

    while (slapCount <= NUM_SLAPS) {
		soundReadValue = soundSensor.getData();
        if (soundReadValue > SOUND_TRIGGER_VALUE) {
            slapCount++;
            if (slapCount == 1) {
				begin = Time::now();
				usleep(POLL_PERIOD);
			}
            if (slapCount == 2) {
                auto end = Time::now();
                fsec fs = end - begin;
                ms elapse = std::chrono::duration_cast<ms>(fs);
                if (elapse.count() < TIME_INTERVAL_ms ) {
					soundRelayActivation = !soundRelayActivation;
					slapCount = 0;
					sleep(1);
                } else {
                    slapCount = 1;
					usleep(POLL_PERIOD);
                    begin = end;
                }
            }
        }
    }
}

void driveByThresholdWithIRSensor()
{
	IRDistanceSensor irSensor = IRDistanceSensor();
	while (1) {
		irRelayActivation = irSensor.getData() > IR_TRIGGER_VALUE;
	}
}


bool BBG_network_cb(Network* net)
{
	// GPIO LED = GPIO(49);
	UdpServer* udp = net->getServer();

	if (soundRelayActivation){
		soundRelayActivation = false;
		soundState = (soundState == SOUND_ON_MSG) ? SOUND_OFF_MSG : SOUND_ON_MSG;
		// std::cout << "soundState:" << soundState << '\n';
		// if (soundState == "sound:on") LED.writeValue(1);
		// if (soundState == "sound:off") LED.writeValue(0);
		udp->send(soundState);
	}

	if (irRelayActivation){
		udp->send(IR_ON_MSG);
		// std::cout << "ir:on" << '\n';
		while (irRelayActivation) {
			/* wait */
		}
		udp->send(IR_OFF_MSG);
		// std::cout << "ir:off" << '\n';
	}

	return true;
}

int main()
{
	cout << "MAIN <------" << endl;

	// start soundSensor thread
	// thread soundSensor (driveByClappingWithSoundSensor);

	// start IR sensor thread
	thread irSensor (driveByThresholdWithIRSensor);

	Network monitor(PORT, RPI_IP, &BBG_network_cb);
	monitor.wait();

	// soundSensor.join();

	irSensor.join();

	return 0;
}
