#pragma once

#include "commands/command_handler.h"
#include "support/network/network.h"
#include <iostream>

class Monitor {
  public:
    Monitor(int port, string host);

    ~Monitor();

    void listen();

    void setCmdHandler(CommandHandler *handler);

    static bool networkCallback(Network *net);

  private:
    CommandHandler *cmdHandler;

    Network *network;
};
