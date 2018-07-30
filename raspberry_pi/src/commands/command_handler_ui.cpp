#include "commands/command_handler_ui.h"
#include "actuators/relay.h"
#include <string>
#include <iostream>
#include <map>
#include <functional>
#include "support/network/network.h"

#define MAX_TOKENS 10
#define HANDLER_NAME_IDX 3
#define PIN_NUM_IDX 2

CommandHandlerUi::CommandHandlerUi() {
  handlers["device_on"] = &CommandHandlerUi::device_on;
  handlers["device_off"] = &CommandHandlerUi::device_off;
  handlers["status"] = &CommandHandlerUi::status;
  handlers["device_status"] = &CommandHandlerUi::device_status;
}

CommandHandlerUi::~CommandHandlerUi() {

}

bool CommandHandlerUi::debounce() {
  return false;
}

void CommandHandlerUi::device_status(string args[], Network *net) {
  cout << "UI ---> CMD: device_status, ARG: " << args[PIN_NUM_IDX] << endl;
  Relay relay(stoi(args[PIN_NUM_IDX]));
  string reply;
  reply += "device_status::";
  reply += args[PIN_NUM_IDX];
  reply += "::";
  reply += relay.getStatus();
  net->getServer()->send(reply);
}

void CommandHandlerUi::status(string args[], Network *net) {
  cout << "UI ---> CMD: status" << endl;
}

void CommandHandlerUi::device_off(string args[], Network *net) {
  cout << "UI ---> CMD: OFF, ARG: " << args[PIN_NUM_IDX] << endl;
  Relay relay(stoi(args[PIN_NUM_IDX]));
  relay.setOff();
}

void CommandHandlerUi::device_on(string args[], Network *net) {
  cout << "UI ---> CMD: ON, ARG: " << args[PIN_NUM_IDX] << endl;
  Relay relay(stoi(args[PIN_NUM_IDX]));
  relay.setOn();
}

void CommandHandlerUi::handle(string msg, Network *net) {
  string tokens[MAX_TOKENS];
  tokenize(msg, tokens);
  if (handlers[tokens[HANDLER_NAME_IDX]]) {
    invoke(handlers[tokens[HANDLER_NAME_IDX]], this, tokens, net);
  }
}
