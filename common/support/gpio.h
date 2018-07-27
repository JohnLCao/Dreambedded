#pragma once

// #define _GLIBCXX_USE_CXX11_ABI 0

#include <string>
#include <fstream>
#include <iostream>

using namespace std;

class GPIO {
private:
    int number;
    string basePath, directionPath, valuePath;
	void writeToFile(string fileName, string value);
	void writeToFile(string fileName, int value);
	int readFromFile(string fileName);

public:
    GPIO (int gpioNumber);
    virtual int readValue();
    virtual void writeValue(int newValue);
    virtual ~GPIO();
};
