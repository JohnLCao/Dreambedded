#include "support/network/network.h"
#include "support/network/udp_server.h"

#include <thread>
#include <iostream>

using namespace std;

Network::Network(int port, string h, bool (*callback)(Network *network)) {
  host = h;
  runnerCallback = callback;
  setRunnerEnabled(true);

  server = new UdpServer(port, host);
  runner = thread(&Network::start, this);
}

void Network::wait() {
  runner.join();
}

void* Network::getContext() {
  return context;
}

UdpServer* Network::getServer() {
  return server;
}

void Network::setContext(void *ctx) {
  context = ctx;
}

void Network::setRunnerEnabled(bool val) {
  isRunnerEnabled = val;
}

bool Network::isServing() {
  return isRunnerEnabled;
}

Network::~Network() {
  setRunnerEnabled(false);
  delete server;
}

void Network::start() {
  while(isServing()) {
    if(!runnerCallback(this)) {
      setRunnerEnabled(false);
    }
  }
}
