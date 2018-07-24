#pragma once

#include <thread>
#include "support/network/udp_server.h"

using namespace std;

// ==========  How to use it:
//
// void *callbackFn(UdpServer *server) {
//   int readBytes;
//   string message = server->receive(&readBytes);
//   cout << message << endl;
//   return NULL;
// }

// int main(int argc, char const *argv[]) {
//   Network network(callbackFn);
//   network.wait();

//   return 0;
// }

class Network {
  public:
    Network(void *(*callback)(UdpServer *server));

    ~Network();

    void wait();

    void start();

  private:
    thread runner;

    UdpServer *server;

    void *(*runnerCallback)(UdpServer *server);

    bool isServing();

    void setRunnerEnabled(bool val);

    bool isRunnerEnabled;
};
