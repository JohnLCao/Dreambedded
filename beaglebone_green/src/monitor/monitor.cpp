/*
 * monitor.cpp
 *
 *  Created on: Jun 25, 2018
 *       Notes:
 */

#include "monitor/monitor.h"
#include <string>
#include <iostream>
#include <thread>
#include <string>
#include <cstdlib>
#include <ratio>
#include <chrono>
#include <unistd.h>
#include "support/network/network.h"

#define POLL_PERIOD 100000
#define TIME_INTERVAL_ms 500
#define SOUND_TRIGGER_VALUE 1500
#define NUM_SAMPLES 10
#define NUM_SLAPS 2
#define SOUND_SENSOR_AIN 4

typedef std::chrono::high_resolution_clock Time;
typedef std::chrono::milliseconds ms;
typedef std::chrono::duration<float> fsec;

using namespace std;

//XXX add #define _GLIBCXX_USE_CXX11_ABI 0  	--as a stop gap.
// 		  before including any C++ libraries.

// status for sensors
int soundRelayActivation = 0;


// function for soundSensor thread
void driveByClappingWithSoundSensor() {
	auto begin = Time::now();
	int soundReadValue = 0;
	int slapCount = 0;
	int reachTriggerValue = 0;

	SoundSensor soundSensor = SoundSensor(SOUND_SENSOR_AIN);
	while (1) {
		slapCount = 0;
        while (slapCount <= NUM_SLAPS) {
            reachTriggerValue = 0;
            for (int i = 0; i < NUM_SAMPLES; i++) {
                soundReadValue = soundSensor.getData();
                if (soundReadValue > SOUND_TRIGGER_VALUE) {
                    // std::cout << soundReadValue << '\n';
                    reachTriggerValue = 1;
                }
            }
            if (reachTriggerValue) {
                slapCount++;
                if (slapCount == 1) begin = Time::now();
                if (slapCount == 2) {
                    auto end = Time::now();
                    fsec fs = end - begin;
                    ms elapse = std::chrono::duration_cast<ms>(fs);
                    if (elapse.count() < TIME_INTERVAL_ms ) {
                        // TODO: toggle relay
						soundRelayActivation = (soundRelayActivation == 1) ? 0 : 1;
						// sleep(5);
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

int main()
{
	cout << "MAIN <------" << endl;
	IRDistanceSensor irSensor = IRDistanceSensor();

	// start soundSensor thread
	thread soundSensor (driveByClappingWithSoundSensor);
//
//	//TODO: this should be moved to the main() / binary for the irSensor.
	irSensor.serveData();
	return 0;
}
