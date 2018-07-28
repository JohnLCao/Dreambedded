#include "commands/command_handler_bb.h"
#include <string>
#include <iostream>
#include <map>
#include <functional>
#include "actuators/relay.h"

#define DEFAULT_PIN 4
#define HANDLER_NAME_IDX 2
#define MAX_TOKENS 2

CommandHandlerBb::CommandHandlerBb() {
  handlers["on"] = &CommandHandlerBb::on;
  handlers["off"] = &CommandHandlerBb::off;
}

CommandHandlerBb::~CommandHandlerBb() {

}

void CommandHandlerBb::handle(string msg) {
  string tokens[MAX_TOKENS];
  tokenize(msg, tokens);
  if (handlers[tokens[HANDLER_NAME_IDX]]) {
    invoke(handlers[tokens[HANDLER_NAME_IDX]], this, tokens);
  }
}

void CommandHandlerBb::on(string args[]) {
  cout << "SENSOR: " << args[0] << " CMD: ON" << endl;
  Relay relay(DEFAULT_PIN);
  relay.setOff();
}

void CommandHandlerBb::off(string args[]) {
  cout << "SENSOR: " << args[0] << " CMD: OFF" << endl;
  Relay relay(DEFAULT_PIN);
  relay.setOff();
}
