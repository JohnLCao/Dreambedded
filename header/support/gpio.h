#ifndef __GPIO_H__
#define __GPIO_H__

#include <string>
#include <fstream>

// #define ADC_PATH "/sys/devices/platform/bone_capemgr/slots"

using namespace std;

class GPIO {
private:
    int number;
    string basePath, directionPath, valuePath;
    static const string EXPORT_FILE = "/sys/class/gpio/export";

public:
    GPIO (int gpioNumber);
    virtual ~ADC ();
    virtual int readValue();
    virtual void GPIO::writeValue(string newValue);
};

#endif
