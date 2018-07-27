#include "support/gpio.h"


GPIO::GPIO(int gpioNumber) {
  string EXPORT_FILE = "/sys/class/gpio/export";
  number        = gpioNumber;
  basePath      = "/sys/class/gpio/gpio" + to_string(gpioNumber);
  directionPath = basePath + "/direction";
  valuePath     = basePath + "/value";

  // Export the GPIO pin
  writeToFile(EXPORT_FILE, gpioNumber);
}

GPIO::~GPIO(){}

int GPIO::readValue() {
    // Set direction to "in"
    writeToFile(this->directionPath.c_str(), "in");
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
  ofstream fs(fileName.c_str());
  if (fs.is_open())
      fs << value;
  else
    cout << "ERROR: cannot open file " << fileName << endl;
  fs.close();
}

void GPIO::writeToFile(string fileName, int value) {
  ofstream fs(fileName.c_str());
  if (fs.is_open())
      fs << value;
  else
    cout << "ERROR: cannot open file " << fileName << endl;
  fs.close();
}

int GPIO::readFromFile(string fileName) {
  int readValue = 0;
  ifstream fs(fileName.c_str());
  if (fs.is_open())
      fs >> readValue;
  else
    cout << "ERROR: cannot open file " << fileName << endl;
  fs.close();
  return readValue;
}
