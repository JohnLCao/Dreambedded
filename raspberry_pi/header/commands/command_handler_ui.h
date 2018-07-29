#pragma once

#include "command_handler.h"
#include <string>
#include "support/network/network.h"

class CommandHandlerUi: public CommandHandler {
  public:
    CommandHandlerUi();

    ~CommandHandlerUi();

    void handle(string msg, Network *net);

    bool debounce();

    // HANDLERS
    void device_off(string args[], Network *net);

    void device_on(string args[], Network *net);

    void device_status(string args[], Network *net);

    void status(string args[], Network *net);

  private:
    map<string, void (CommandHandlerUi::*)(string args[], Network *net)> handlers;
};
