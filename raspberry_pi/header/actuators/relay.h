#pragma once

class Relay {
  public:
    Relay(int p);

    ~Relay();

    void setOn();

    void setOff();

  private:
    int pin;
};
