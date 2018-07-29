#include "monitor/monitor.h"
// #include "actuators/relay.h"
#include "support/network/network.h"
#include "support/network/udp_server.h"
#include "commands/command_handler.h"

#include <iostream>

bool Monitor::networkCallback(Network *net) {
  int bytesRead;
  string reply = net->getServer()->receive(&bytesRead);

  Monitor *ctx = (Monitor *)(net->getContext());

  if (!ctx->cmdHandler->debounce()) {
    cout << "REPLY: " << reply << endl;
    ctx->cmdHandler->handle(reply, net);
  } else {
    cout << "Monitor: debounce" << endl;
  }

  return true;
}

Monitor::Monitor(int port, string host) {
  network = new Network(port, host, &Monitor::networkCallback);
  network->setContext((void *)this);
}

Monitor::~Monitor() {
  delete network;
}

void Monitor::setCmdHandler(CommandHandler *handler) {
  cmdHandler = handler;
}

void Monitor::listen() {
  network->wait();
}
