#pragma once

#include <thread>
#include "support/network/udp_server.h"

using namespace std;

// ==========  How to use it:
//
// bool callbackFn(UdpServer *server) {
//   int readBytes;
//   string message = server->receive(&readBytes);
//   cout << message << endl;
//   // Should return false when you want to abort
//   return true;
// }

// int main(int argc, char const *argv[]) {
//   Network network(callbackFn);
//   network.wait();

//   return 0;
// }

class Network {
  public:
    Network(int port, bool (*callback)(Network *network));
    ~Network();
    void wait();
    void setContext(void *ctx);
    void* getContext();
    UdpServer* getServer();

  private:
    void *context;
    thread runner;
    UdpServer *server;
    void start();
    bool (*runnerCallback)(Network *network);
    bool isServing();
    void setRunnerEnabled(bool val);
    bool isRunnerEnabled;
};
