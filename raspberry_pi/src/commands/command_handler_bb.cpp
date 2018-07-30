#include <string>
#include <iostream>
#include <map>
#include <functional>
#include <chrono>
#include "commands/command_handler_bb.h"
#include "actuators/relay.h"
#include "support/network/network.h"

#define DEFAULT_PIN 4
#define HANDLER_NAME_IDX 1
#define MAX_TOKENS 2
#define DEBOUNCE_BB_REPLY_IN_MS 1000

CommandHandlerBb::CommandHandlerBb() {
  handlers["on"] = &CommandHandlerBb::on;
  handlers["off"] = &CommandHandlerBb::off;
  lastReplyTime = chrono::high_resolution_clock::now();
}

CommandHandlerBb::~CommandHandlerBb() {

}

void CommandHandlerBb::handle(string msg, Network *net) {
  string tokens[MAX_TOKENS];
  tokenize(msg, tokens);
  string key = tokens[HANDLER_NAME_IDX];

  if (handlers[key]) {
    invoke(handlers[key], this, tokens);
    lastReplyTime = chrono::high_resolution_clock::now();
  }
}

void CommandHandlerBb::on(string args[]) {
  cout << "SENSOR: " << args[0] << " CMD: ON" << endl;
  Relay relay(DEFAULT_PIN);
  relay.setOn();
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
