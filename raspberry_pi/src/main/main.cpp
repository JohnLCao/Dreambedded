#include <iostream>

#include "actuators/relay.h"
#include "networking/udp_server.h"

using namespace std;

int main(int argc, char const *argv[]) {
  UdpServer server(22110);

  while (1) {
    int bytesRead;
    string reply = server.receive(&bytesRead);
    cout << reply << endl;
    server.send(reply);
  }

  return 0;
}
