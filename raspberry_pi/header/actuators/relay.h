#pragma once

#include <string>

using namespace std;

class Relay {
  public:
    Relay(int p);

    ~Relay();

    void setOn();

    void setOff();

    string getStatus();

  private:
    int pin;
};
