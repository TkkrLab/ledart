#ifndef __NETWORK_H__
#define __NETWORK_H__

#include <memory>
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
#include <graphics/surface.h>
#include <outputs/interface.h>

#define MAX_UDP_PACKETSIZE 1024

class Network: public Interface
{
public:
    Network(YAML::Node);
    ~Network();
    void open();
    void transmit(uint8_t *, size_t);
    void set_port(uint16_t);
    uint16_t get_port();
private:
    uint16_t port;
    int sockfd;
    struct sockaddr_in addr;
    std::string target = "";
};

#endif
