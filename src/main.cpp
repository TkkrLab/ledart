#include <stdio.h>
#include <network.h>

#define MATRIX_WIDTH 96
#define MATRIX_HEIGHT 48

char target[] = "10.42.3.12";

class Lmcp: public Network
{
public:
    void send(uint8_t *, size_t, char *);
    void send_command(uint8_t);
private:
    static const uint8_t WRITE_BUFF = 0x01;
    static const uint8_t CLEAR = 0x02;
    static const uint8_t DRAW_ROWS = 0x10;
    static const uint8_t DRAW_IMG_RECT = 0x11;
    static const uint8_t WRITE_TEXT_LN_BASED = 0x20;
    static const uint8_t WRITE_TEXT_ABSOLUTE = 0x21;
};

void Lmcp::send_command(uint8_t command)
{
    static uint8_t data[1];

    data[0] = command;
    transmit(data, 1, target);
}

void Lmcp::send(uint8_t *image, size_t size, char *target)
{
    static uint8_t x, y, width, height;
    static uint8_t data[MAX_UDP_PACKETSIZE];
    // 5 bytes are used for command bytes.
    // so if image is bigger then what fits a udp packet.
    // then we have some magic to figure out.
    if(size > (MAX_UDP_PACKETSIZE - 5))
    {
        return;
    }
    else
    {
        // setup first part of packet.
        data[0] = DRAW_IMG_RECT;
        data[1] = x;
        data[2] = y;
        data[3] = MATRIX_WIDTH;
        data[4] = MATRIX_HEIGHT;

        printf("Draw_IMG_RECT: %d\n"
               "x:%d\n"
               "y:%d\n"
               "width:%d\n"
               "height:%d\n",
               data[0],
               data[1],
               data[2],
               data[3],
               data[4]);

        // copy in our data.
        int i;
        for(i = 0;i < size; i++)
        {
            data[i+5] = image[i];
            printf("|%d:%d:%d|\n", i, i + 5, data[i+5]);
        }
        // transmit data and display it on the ledboard.
        transmit(data, size, target);
        send_command(WRITE_BUFF);
    }
}

void networkTest()
{
    Network net = Network();
    uint8_t data[1024] = {0x02};
    net.send(data, 1024, target);
}

int main(int argc, char **argv)
{
    // Lmcp lmcp = Lmcp();
    // static uint8_t data[1019];

    // int i;
    // for(i = 0;i < 0xff; i++)
    // {
    //     data[i] = i;
    // }

    // lmcp.send(data, 1019, target);

    Network net = Network();
    static uint8_t clear[1024] = {0x02};
    static uint8_t writeout[1024] = {0x01};
    static uint8_t data[6] = {0x11, 0, 0, 1, 1, 0xff};

    net.send(clear, 1, target);
    net.send(data, 6, target);
    net.send(writeout, 1, target);
    net.send(writeout, 1, target);
    net.send(writeout, 1, target);
    net.send(writeout, 1, target);
    net.send(writeout, 1, target);
    // networkTest();
    return 0;
}