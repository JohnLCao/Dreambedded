#pragma once

#include "command_handler.h"
#include <string>
#include <chrono>

class CommandHandlerBb: public CommandHandler {
  public:
    CommandHandlerBb();

    ~CommandHandlerBb();

    void handle(string msg);

    bool debounce();

    // HANDLERS
    void on(string args[]);

    void off(string args[]);


  private:
    map<string, void (CommandHandlerBb::*)(string args[])> handlers;
    chrono::time_point<chrono::high_resolution_clock> lastReplyTime;
};
