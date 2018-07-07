#include "adc.h"
#include <string>
#include <iostream>
#include <fstream>

ADC::ADC(int AINNumber) {
  number = number;
  path   = "/sys/bus/iio/devices/iio:device0/in_voltage" + to_string(AINNumber) + "_raw";
}

virtual int ADC::readValue() {
  int readValue;
  ifstream fs(this.path);
  if (fs.is_open())
  {
      cout << "Reading from a file:" << endl;
      fs >> readValue;
  } else {
    cout << "ERROR: cannot open file " << this.path << endl;
  }
  myfile.close();
  return readValue;
}
