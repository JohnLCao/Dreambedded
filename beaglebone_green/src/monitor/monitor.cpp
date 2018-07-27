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
#include <cstdlib>
#include <ratio>
#include <chrono>
#include <unistd.h>
#include "support/network/network.h"
#include "sensors/sound_sensor.h"
#include "sensors/ir_distance_sensor.h"
#include "support/gpio.h"

#define POLL_PERIOD 100000
#define TIME_INTERVAL_ms 500
#define SOUND_TRIGGER_VALUE 1200
#define IR_TRIGGER_VALUE 1000
#define NUM_SAMPLES 10
#define NUM_SLAPS 2
#define SOUND_SENSOR_AIN 4
#define IR_SENSOR_AIN	 1

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

			while (reachTriggerValue && soundSensor.getData() > normalReadingValue) {
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

void driveByThreasholdWithIRSensor()
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
				usleep(10000);
			} else {
				break;
			}
		}
		//IR sensor will turn light off if no one is in the room
		irRelayActivation = (triggerTimes == NUM_SAMPLES);
	}
}

// void test() {
// 	GPIO LED = GPIO(49);
//
// 	while (1) {
// 		if (soundRelayActivation) {
// 			// std::cout << "ON" << '\n';
// 			LED.writeValue(1);
// 			while (soundRelayActivation) {
// 				// do nothing
// 			}
// 		} else {
// 			// std::cout << "OFF" << '\n';
// 			LED.writeValue(0);
// 			while (!soundRelayActivation) {
// 				/* code */
// 			}
// 		}
// 	}
// }

int main()
{
	cout << "MAIN <------" << endl;

	// start soundSensor thread
	thread soundSensor (driveByClappingWithSoundSensor);
	// start IR sensor thread
	thread irSensor (driveByThreasholdWithIRSensor);

	// thread testLED (test);

	soundSensor.join();
	irSensor.join();
	// testLED.join();

	return 0;
}
