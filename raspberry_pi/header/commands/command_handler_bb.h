#pragma once

#include "command_handler.h"
#include <string>

class CommandHandlerBb: public CommandHandler {
  public:
    CommandHandlerBb();

    ~CommandHandlerBb();

    void handle(string msg);

    // HANDLERS
    void on(string args[]);

    void off(string args[]);

  private:
    map<string, void (CommandHandlerBb::*)(string args[])> handlers;
};
