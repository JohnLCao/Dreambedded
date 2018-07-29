#pragma once

#include "command_handler.h"
#include <string>
#include <chrono>
#include "support/network/network.h"

class CommandHandlerBb: public CommandHandler {
  public:
    CommandHandlerBb();

    ~CommandHandlerBb();

    void handle(string msg, Network *net);

    bool debounce();

    // HANDLERS
    void on(string args[]);

    void off(string args[]);


  private:
    map<string, void (CommandHandlerBb::*)(string args[])> handlers;
    chrono::time_point<chrono::high_resolution_clock> lastReplyTime;
};
