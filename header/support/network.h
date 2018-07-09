#ifndef __MONITOR_H__
#define __MONITOR_H__

#include <string>
using namespace std;

/*
network.h
A network module that spawns a background thread to detect incoming packets
(from say, the Raspberry Pi) and send packets
*/
class Network {
private:
    static const int MSG_MAX_LEN = 1500;

    // Runner thread
    void* thread(void* args);
    pthread_t tid;

    // UDP networking attributes
    int port;
    struct sockaddr_in socket_in;
    unsigned int sinLen;
    int socketDescriptor;

    char message[MSG_MAX_LEN];
    char response[MSG_MAX_LEN];

public:
    Network(int portNumber);
    ~Network() {};
    //void sendPacket(string message);
    void sendPacket();
};

#endif
