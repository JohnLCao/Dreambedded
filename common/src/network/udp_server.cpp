#include "support/network/udp_server.h"

#include <unistd.h> // for close
#include <netdb.h>
#include <string>
#include <iostream>

#define MAX_MSG_SIZE 64000

UdpServer::UdpServer(){};

UdpServer::UdpServer(int _port): port(_port) {
  addressInfo.sin_family = AF_INET;
  addressInfo.sin_addr.s_addr = htonl(INADDR_ANY);
  addressInfo.sin_port = htons(port);

  descriptor = socket(PF_INET, SOCK_DGRAM, 0);

  bind(
    descriptor,
    (struct sockaddr*) &addressInfo,
    sizeof(addressInfo)
  );
}

UdpServer::~UdpServer() {
  close(descriptor);
}

void UdpServer::send(string msg) {
  sendto(descriptor,
    msg.c_str(),
    msg.size(),
    0,
    (struct sockaddr *) &addressInfo,
    sizeof(addressInfo)
  );
}

int UdpServer::getPort() const {
  return port;
}

string UdpServer::receive(int *bytesRead) {
  unsigned int addrInfoLen = sizeof(addressInfo);
  char msg[MAX_MSG_SIZE];

  *bytesRead = recvfrom(
    descriptor,
    msg,
    MAX_MSG_SIZE-1,
    0,
    (struct sockaddr *) &addressInfo,
    &(addrInfoLen)
  );

  msg[*bytesRead] = 0;
  return string(msg);
}
