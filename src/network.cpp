#include "network.h"

Network::Network(uint16_t port)
{
    this->port = port;
    printf("port: %d\n", port);
    this->open();
}

void Network::open()
{
    this->sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if(this->sockfd < 0)
    {
        printf("Unable to create socket.\n");
        exit(0);
    }
    // clear address structure.
    memset((char *)&this->addr, 0, sizeof(this->addr));
    // fill with non changing data.
    this->addr.sin_family = AF_INET;
    this->addr.sin_port = htons(this->port);
}


void Network::transmit(uint8_t *data, size_t size, char *target)
{
    inet_pton(AF_INET, target, &(this->addr.sin_addr));
    int res = sendto(this->sockfd, data, size, 0, (struct sockaddr *)&addr, sizeof(addr));
    if(res < 0)
    {
        printf("Unable to send to socket.\n");
        exit(0);
    }
}

/*
  this function is what
  you should override to implement protocol specifics.
*/
void Network::send(Surface &surface, char *target)
{
}

void Network::set_port(uint16_t port)
{
    this->port = port;
    this->addr.sin_port = port;
}

uint16_t Network::get_port()
{
    return this->port;
}

Network::~Network()
{
    shutdown(this->sockfd, 2);
}