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
#define PORT					22222
#define RPI_IP 					"142.58.82.120"
#define IR_ON_MSG  				"ir:on"
#define IR_OFF_MSG				"ir:off"
#define SOUND_ON_MSG			"sound:on"
#define SOUND_OFF_MSG			"sound:off"
#define BUILD_IR				1
#define BUILD_SOUND				1

typedef std::chrono::high_resolution_clock Time;
typedef std::chrono::milliseconds ms;
typedef std::chrono::duration<float> fsec;

using namespace std;

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

		udp->send(soundState);
	}

	if (irRelayActivation){
		udp->send(IR_ON_MSG);
		while (irRelayActivation) {
			/* wait */
		}
		udp->send(IR_OFF_MSG);
	}

	return true;
}

int main()
{
	cout << "MAIN <------" << endl;

	Network monitor(PORT, RPI_IP, &BBG_network_cb);
	monitor.wait();

	if (BUILD_SOUND) {
		// start soundSensor thread
		thread soundSensor (driveByClappingWithSoundSensor);
		soundSensor.join();
	}
	if (BUILD_IR){
		// start IR sensor thread
		thread irSensor (driveByThresholdWithIRSensor);
		irSensor.join();
	}

	return 0;
}
