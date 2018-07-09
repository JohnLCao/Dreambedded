#include "gpio.h"
#include <string>
#include <iostream>
#include <fstream>

GPIO::GPIO(int gpioNumber) {
  number        = gpioNumber;
  basePath      = "/sys/class/gpio/gpio" + to_string(gpioNumber);
  directionPath = basePath + "/direction";
  valuePath     = basePath + "/value";

  // Export the GPIO pin
  writeToFile(EXPORT_FILE, gpioNumber);
}

int GPIO::readValue() {
    // Set direction to "in"
    writeToFile(this->directionPath, "in");
    return readFromFile(this->valuePath);
}

void GPIO::writeValue(int newValue) {
    // Set direction to "out"
    writeToFile(this->directionPath, "out");
    writeToFile(this->valuePath, newValue);
}

// private functions
// TODO: decide what to return if read/write to files fails
void GPIO::writeToFile(string fileName, string value) {
  ofstream fs(fileName);
  if (fs.is_open())
      fs << value;
  else
    cout << "ERROR: cannot open file " << fileName << endl;
  fs.close();
}

void GPIO::writeToFile(string fileName, int value) {
  ofstream fs(fileName);
  if (fs.is_open())
      fs << value;
  else
    cout << "ERROR: cannot open file " << fileName << endl;
  fs.close();
}

int GPIO::readFromFile(string fileName) {
  int readValue = 0;
  ifstream fs(fileName);
  if (fs.is_open())
      fs >> readValue;
  else
    cout << "ERROR: cannot open file " << fileName << endl;
  fs.close();
  return readValue;
}
