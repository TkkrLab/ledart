#ifndef __NETWORK_H__
#define __NETWORK_H__

#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdint.h>
#include <string.h>

#define MAX_UDP_PACKETSIZE 1024

class Network
{
public:
    Network(uint16_t port=1337);
    ~Network();
    void open();
    void transmit(uint8_t*, size_t, char*);
    virtual void send(uint8_t*, size_t, char*);
    void set_port(uint16_t);
    uint16_t get_port();
private:
    uint16_t port;
    int sockfd;
    struct sockaddr_in addr;
};

#endif