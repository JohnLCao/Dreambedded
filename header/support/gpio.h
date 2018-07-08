#pragma once

#include <string>
#include <fstream>

#define GPIO_PATH "sys/class/gpio"
enum GPIO_DIRECTION{ INPUT, OUTPUT };
enum GPIO_VALUE{ LOW=0, HIGH=1 };

using namespace std;

class GPIO {
private:
	int number;
	string path;

	// functions
	int exportGPIO();
	int unexportGPIO();

public:
	GPIO();
	GPIO(int gpioNumber);
	int setDirection(GPIO_DIRECTION);
	GPIO_DIRECTION getDirection();
	int setValue(GPIO_VALUE);
	GPIO_VALUE getValue();
};
