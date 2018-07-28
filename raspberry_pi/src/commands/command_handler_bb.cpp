#include <string>
#include <iostream>
#include <map>
#include <functional>
#include <chrono>
#include "commands/command_handler_bb.h"
#include "actuators/relay.h"

#define DEFAULT_PIN 4
#define HANDLER_NAME_IDX 2
#define MAX_TOKENS 2
#define DEBOUNCE_BB_REPLY_IN_MS 1000

CommandHandlerBb::CommandHandlerBb() {
  handlers["on"] = &CommandHandlerBb::on;
  handlers["off"] = &CommandHandlerBb::off;
  lastReplyTime = chrono::high_resolution_clock::now();
}

CommandHandlerBb::~CommandHandlerBb() {

}

void CommandHandlerBb::handle(string msg) {
  string tokens[MAX_TOKENS];
  tokenize(msg, tokens);
  if (handlers[tokens[HANDLER_NAME_IDX]]) {
    invoke(handlers[tokens[HANDLER_NAME_IDX]], this, tokens);
    lastReplyTime = chrono::high_resolution_clock::now();
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

bool CommandHandlerBb::debounce() {
  auto now = chrono::high_resolution_clock::now();
  chrono::duration<float> elapsed = now - lastReplyTime;

  bool reply;

  if (chrono::duration_cast<chrono::milliseconds>(elapsed).count() > DEBOUNCE_BB_REPLY_IN_MS) {
    reply = false;
  } else {
    reply = true;
  }

  return reply;
}
