#pragma once

#include "command_handler.h"
#include <string>

class CommandHandlerBb: public CommandHandler {
  public:
    CommandHandlerBb();

    ~CommandHandlerBb();

    void handle(string msg);
};
