#pragma once

#include <unistd.h> // for close
#include <netdb.h>
#include <string>

using namespace std;

class UdpServer {
  public:
    UdpServer(int port);

    UdpServer();

    ~UdpServer();

    int getPort() const;

    void send(string msg);

    string receive(int *bytesRead);

  private:
    int descriptor;
    int port;

    struct sockaddr_in addressInfo;
};
