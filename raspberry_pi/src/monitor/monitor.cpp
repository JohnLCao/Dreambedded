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
  ctx->cmdHandler->handle(reply);

  return true;
}

Monitor::Monitor(int port) {
  network = new Network(port, &Monitor::networkCallback);
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
