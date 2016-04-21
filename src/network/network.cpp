#include "network.h"

Network::Network(uint16_t port, char *target)
{
    // this->target = target;
    if(this->target == NULL || target == NULL)
    {
        strcpy(this->target, "127.0.0.1");
    }
    else
    {
        strcpy(this->target, target);
    }
    this->port = port;
    printf("target: %s:%d\n", this->target, this->port);
    this->open();
}

void Network::open()
{
    this->sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if(this->sockfd < 0)
    {
        fprintf(stderr, "Unable to create socket. errno: %s\n", strerror(errno));
        exit(-1);
    }
    // clear address structure.
    memset((char *)&this->addr, 0, sizeof(this->addr));
    // fill with non changing data.
    this->addr.sin_family = AF_INET;
    this->addr.sin_port = htons(this->port);
    inet_pton(AF_INET, this->target, &(this->addr.sin_addr));
}


void Network::transmit(uint8_t *data, size_t size)
{
    // this->open();
    static timeval t = {0, 0};
    static fd_set wset;
    static int maxfdp1 = this->sockfd + 1;
    FD_ZERO(&wset);
    FD_SET(this->sockfd, &wset);

    int res = select(maxfdp1, NULL, &wset, NULL, &t);
    if(res < 0)
    {
        fprintf(stderr, "select error. errno: %s\n", strerror(errno));
        exit(-1);
    }
    if(FD_ISSET(this->sockfd, &wset))
    {
        int res = sendto(this->sockfd, data, size, MSG_DONTWAIT,
                         (struct sockaddr *)&addr, sizeof(addr));
        if(res < 0)
        {
            fprintf(stderr, "Unable to send to socket. errno: %s\n", strerror(errno));
            exit(1);
        }
    }
    // close(this->sockfd);
}

/*
  this function is what
  you should override to implement protocol specifics.
*/
void Network::process(Surface *surface)
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
    close(this->sockfd);
}