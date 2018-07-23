#include "support/network/network.h"
#include "support/network/udp_server.h"

#include <thread>
#include <iostream>
#include <iostream>

using namespace std;

Network::Network(void *(*callback)(UdpServer *server)) {
  runnerCallback = callback;
  setRunnerEnabled(true);
  server = new UdpServer(22222);
  runner = thread(&Network::start, this);
}

void Network::wait() {
  runner.join();
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
    runnerCallback(server);
  }
}
