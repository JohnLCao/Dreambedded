#include "actuators/relay.h"
#include "support/gpio.h"
#include <string>

#define ON_VALUE 0
#define OFF_VALUE 1

Relay::Relay(int p) {
  pin = p;
}

Relay::~Relay() {

}

string Relay::getStatus() {
  GPIO gpio(pin);
  string reply = !gpio.readValue() ? "on" : "off";
  return reply;
}

void Relay::setOn() {
  GPIO gpio(pin);
  gpio.writeValue(ON_VALUE);
}

void Relay::setOff() {
  GPIO gpio(pin);
  gpio.writeValue(OFF_VALUE);
}
