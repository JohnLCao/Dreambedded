#include <iostream>

#include "actuators/relay.h"
#include "support/network/network.h"
#include "support/network/udp_server.h"

using namespace std;

void *callbackFn(UdpServer *server) {
  int readBytes;
  string message = server->receive(&readBytes);
  cout << message << endl;
  return NULL;
}

int main(int argc, char const *argv[]) {
  Network network(callbackFn);
  network.wait();

  return 0;
}
