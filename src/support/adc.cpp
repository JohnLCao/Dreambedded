#include "adc.h"
#include <string>
#include <iostream>
#include <fstream>

ADC::ADC(int AINNumber) {
  number = AINNumber;
  path   = "/sys/bus/iio/devices/iio:device0/in_voltage" + to_string(AINNumber) + "_raw";
}

int ADC::readValue() {
    int readValue;
    ifstream fs(this.path);
    if (fs.is_open())
      fs >> readValue;
    else
        cout << "ERROR: cannot open file " << this.path << endl;
    fs.close();
    return readValue;
}
