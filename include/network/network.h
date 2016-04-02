#ifndef __NETWORK_H__
#define __NETWORK_H__

#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>

#include <surface.h>

#define MAX_UDP_PACKETSIZE 1024

class Network
{
public:
    Network(uint16_t port=1337, char *target=NULL);
    ~Network();
    void open();
    void transmit(uint8_t *, size_t);
    virtual void send(Surface&);
    void set_port(uint16_t);
    uint16_t get_port();
private:
    uint16_t port;
    int sockfd;
    struct sockaddr_in addr;
    char target[20];
};

#endif