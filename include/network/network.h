#ifndef __NETWORK_H__
#define __NETWORK_H__

#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <sys/time.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

#include <mtools.h>
#include <surface.h>

#define MAX_UDP_PACKETSIZE 1024

class Network
{
public:
    Network(const char *target=NULL, uint16_t port=1337);
    ~Network();
    void open();
    void transmit(uint8_t *, size_t);
    virtual void process(Surface *);
    void set_port(uint16_t);
    uint16_t get_port();
private:
    uint16_t port;
    int sockfd;
    struct sockaddr_in addr;
    char target[20];
};

#endif