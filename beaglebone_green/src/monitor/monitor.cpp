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

#define POLL_PERIOD 100000
#define TIME_INTERVAL_ms 700
#define SOUND_TRIGGER_VALUE 1200
#define IR_TRIGGER_VALUE 1600
#define NUM_SLAPS 2
#define SOUND_SENSOR_AIN 4
#define IR_SENSOR_AIN	 1
#define STOP 			"stop"
#define STATUS 			"status"
#define PORT			22222
#define RPI_IP 			"142.58.82.120"
#define BBG_IP			""

typedef std::chrono::high_resolution_clock Time;
typedef std::chrono::milliseconds ms;
typedef std::chrono::duration<float> fsec;

using namespace std;

//XXX add #define _GLIBCXX_USE_CXX11_ABI 0  	--as a stop gap.
// 		  before including any C++ libraries.

// status for sensors
bool soundRelayActivation = false;
bool irRelayActivation = false;
string soundState = "sound:off";

// function for soundSensor thread
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

void driveByThreasholdWithIRSensor()
{
	IRDistanceSensor irSensor = IRDistanceSensor();
	while (1) {
		irRelayActivation = irSensor.getData() > IR_TRIGGER_VALUE;
	}
}

bool BBG_network_cb(Network* net)
{
	UdpServer* udp = net->getServer();

	if (soundRelayActivation){
		soundRelayActivation = false;
		soundState = (soundState == "sound:on") ? "sound:off" : "sound:on";
		std::cout << "soundState:" << soundState << '\n';
		udp->send(soundState);
	}

	if (irRelayActivation){
		udp->send("ir:on");
		while (irRelayActivation) {
			/* wait */
		}
		udp->send("ir:off");
	}

	return true;
}

int main()
{
	cout << "MAIN <------" << endl;

	// start soundSensor thread
	thread soundSensor (driveByClappingWithSoundSensor);

	// start IR sensor thread
	thread irSensor (driveByThreasholdWithIRSensor);

	Network monitor(PORT, RPI_IP, &BBG_network_cb);
	monitor.wait();

	soundSensor.join();

	irSensor.join();

	return 0;
}
