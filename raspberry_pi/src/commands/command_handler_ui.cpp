#include "commands/command_handler_ui.h"
#include "actuators/relay.h"
#include <string>
#include <iostream>
#include <map>
#include <functional>

#define MAX_TOKENS 10

static string messageDelimeter = "::";

static void tokenize(string msg, string tokens[]);

CommandHandlerUi::CommandHandlerUi() {
  handlers["device_on"] = &CommandHandlerUi::device_on;
  handlers["device_off"] = &CommandHandlerUi::device_off;
}

CommandHandlerUi::~CommandHandlerUi() {

}

void CommandHandlerUi::device_off(string args[]) {
  Relay relay(stoi(args[2]));
  relay.setOff();
}

void CommandHandlerUi::device_on(string args[]) {
  Relay relay(stoi(args[2]));
  relay.setOn();
}

void CommandHandlerUi::handle(string msg) {
  string tokens[MAX_TOKENS];
  tokenize(msg, tokens);
  if (handlers[tokens[3]]) {
    invoke(handlers[tokens[3]], this, tokens);
  }
}

static void tokenize(string msg, string tokens[]) {
  int cursor = 0;
  size_t position = msg.find(messageDelimeter);
  string token;

  while (position != string::npos) {
    token = msg.substr(0, position);
    tokens[cursor] = token;
    msg.erase(0, position + messageDelimeter.length());
    position = msg.find(messageDelimeter);
    cursor += 1;
  }

  tokens[cursor] = msg;
}
