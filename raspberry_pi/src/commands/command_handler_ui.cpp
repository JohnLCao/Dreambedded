#include "commands/command_handler_ui.h"
#include "actuators/relay.h"
#include <string>
#include <iostream>
#include <map>
#include <functional>

#define MAX_TOKENS 10
#define HANDLER_NAME_IDX 3
#define PIN_NUM_IDX 2

CommandHandlerUi::CommandHandlerUi() {
  handlers["device_on"] = &CommandHandlerUi::device_on;
  handlers["device_off"] = &CommandHandlerUi::device_off;
}

CommandHandlerUi::~CommandHandlerUi() {

}

void CommandHandlerUi::device_off(string args[]) {
  cout << "UI ---> CMD: OFF, ARG: " << args[PIN_NUM_IDX] << endl;
  Relay relay(stoi(args[PIN_NUM_IDX]));
  relay.setOff();
}

void CommandHandlerUi::device_on(string args[]) {
  cout << "UI ---> CMD: ON, ARG: " << args[PIN_NUM_IDX] << endl;
  Relay relay(stoi(args[PIN_NUM_IDX]));
  relay.setOn();
}

void CommandHandlerUi::handle(string msg) {
  string tokens[MAX_TOKENS];
  tokenize(msg, tokens);
  if (handlers[tokens[HANDLER_NAME_IDX]]) {
    invoke(handlers[tokens[HANDLER_NAME_IDX]], this, tokens);
  }
}
