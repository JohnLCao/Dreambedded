#include "support/adc.h"

#define ADC_PREFIX "/sys/bus/iio/devices/iio:device0/in_voltage"
#define ADC_SUFFIX "_raw"

//constructors and destructors
ADC::ADC(){}
ADC::~ADC(){}

ADC::ADC(int AINNumber)
{
  number = AINNumber;
  path   = "/sys/bus/iio/devices/iio:device0/in_voltage0_raw";
}

//
int ADC::readValue()
{
  int readValue;
  ifstream fs(path.c_str());
  if (fs.is_open())
  {
      // cout << "Reading from a file:" << endl;
      fs >> readValue;
  } else {
    cout << "ERROR: cannot open file " << path << endl;
  }
  fs.close();
  return readValue;
}

