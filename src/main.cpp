#include <stdio.h>
#include <network.h>

Network net = Network();

int main(int argc, char **argv)
{
    uint8_t data[1024] = {0x02};
    char ip[] = "10.42.3.12";
    while(1)
    {
        net.send(data, 1024, ip);
    }
    return 0;
}