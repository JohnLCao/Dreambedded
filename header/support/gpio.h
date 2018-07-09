#pragma once

#include <string>
#include <fstream>

using namespace std;

class GPIO {
private:
    int number;
    string basePath, directionPath, valuePath;
    string EXPORT_FILE = "/sys/class/gpio/export";
		void writeToFile(string fileName, string value);
		void writeToFile(string fileName, int value);
		int readFromFile(string fileName);

public:
    GPIO (int gpioNumber);
    virtual int readValue();
    virtual void writeValue(int newValue);
};
