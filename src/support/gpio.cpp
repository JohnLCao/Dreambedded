#include "gpio.h"
#include <string>
#include <iostream>
#include <fstream>

GPIO::GPIO(int gpioNumber) {
  number        = number;
  basePath      = "/sys/class/gpio/gpio" + to_string(gpioNumber);
  directionPath = basePath + "/direction";
  valuePath     = basePath + "/value";

  // Export the GPIO pin
  ofstream fs(GPIO::EXPORT_FILE);
  if (fs.is_open()) {
      fs << to_string(gpioNumber);
  } else {
    cout << "ERROR: cannot open file " << GPIO::EXPORT_FILE << endl;
  }
  fs.close();
}

virtual void GPIO::setDirection(string value) {
    ofstream fs(this.directionPath);
    if (fs.is_open())
    {
      fs << value;
    } else {
        cout << "ERROR: cannot open file " << this.valuePath << endl;
    }
    fs.close();
}

virtual int GPIO::readValue() {
    // Set direction to "in"
    setDirection("in");

    int readValue;
    ifstream fs(this.valuePath);
    if (fs.is_open())
    {
      fs >> readValue;
    } else {
        cout << "ERROR: cannot open file " << this.valuePath << endl;
    }
    fs.close();
    return readValue;
}

virtual void GPIO::writeValue(string newValue) {
    // Set direction to "out"
    setDirection("out");

    ofstream fs(this.valuePath);
    if (fs.is_open())
    {
      fs << newValue;
    } else {
        cout << "ERROR: cannot open file " << this.valuePath << endl;
    }
    fs.close();
}
