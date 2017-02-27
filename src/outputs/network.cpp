#include "outputs/network.h"

int hostname_to_ip(const char *hostname, char *ip)
{
    struct hostent *he;
    struct in_addr **addr_list;

    if((he = gethostbyname(hostname)) == NULL)
    {
        // get host info
        herror("gethostbyname");
        return 1;
    }

    addr_list = (struct in_addr **)he->h_addr_list;
    for(int i = 0; addr_list[i] != NULL; i++)
    {
        // return the first one
        strcpy(ip, inet_ntoa(*addr_list[i]));
        return 0;
    }
    return 1;
}

Network::Network(YAML::Node args)
{
    char temp_target[20];
    this->target = get_arg<std::string>(args["target"], "127.0.0.1");
    this->port = get_arg<int>(args["port"], 1337);

    if(hostname_to_ip(target.c_str(), temp_target))
    {
        fprintf(stderr, "Failed to resolve hostname! exiting.\n");
        exit(1);
    }
    else
    {
        this->target = temp_target;
        printf("[%s] resolved to [%s].\n", target.c_str(), this->target.c_str());
    }

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
    inet_pton(AF_INET, this->target.c_str(), &(this->addr.sin_addr));
}


void Network::transmit(uint8_t *data, size_t size)
{
    // this->open();
    timeval t = {0, 0};
    fd_set wset;
    int maxfdp1 = this->sockfd + 1;
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
    ::close(this->sockfd);
}
