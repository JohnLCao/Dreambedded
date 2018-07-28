#pragma once

#include "command_handler.h"
#include <string>

class CommandHandlerUi: public CommandHandler {
  public:
    CommandHandlerUi();

    ~CommandHandlerUi();

    void handle(string msg);

    // HANDLERS
    void device_off(string args[]);

    void device_on(string args[]);

  private:
    map<string, void (CommandHandlerUi::*)(string args[])> handlers;
};
