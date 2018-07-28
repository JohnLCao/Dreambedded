#include "actuators/relay.h"
#include "support/gpio.h"

#define ON_VALUE 0
#define OFF_VALUE 1

Relay::Relay(int p) {
  pin = p;
}

Relay::~Relay() {

}

void Relay::setOn() {
  GPIO gpio(pin);
  gpio.writeValue(ON_VALUE);
}

void Relay::setOff() {
  GPIO gpio(pin);
  gpio.writeValue(OFF_VALUE);
}
