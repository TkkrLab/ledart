#include <stdio.h>
#include <network.h>
#include <surface.h>

#define MATRIX_WIDTH 96
#define MATRIX_HEIGHT 48

char target[] = "127.0.0.1";

class Lmcp: public Network
{
public:
    void send(Surface &, char *);
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

void Lmcp::send(Surface &surf, char *target)
{
}

// void networkTest()
// {
//     Network net = Network();
//     uint8_t data[1024] = {0x02};
//     net.send(data, 1024, target);
// }

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

    // Network net = Network();
    static uint8_t clear[1024] = {0x02};
    static uint8_t writeout[1024] = {0x01};
    static uint8_t data[(31 * 31) + 5] = {0x11, 0, 0, 1, 1, 0xff};

    // net.send(clear, 1, target);
    // net.send(data, 6, target);
    // net.send(writeout, 1, target);
    // net.send(writeout, 1, target);
    // net.send(writeout, 1, target);
    // net.send(writeout, 1, target);
    // net.send(writeout, 1, target);
    // networkTest();

    Network net = Network();
    Surface surf = Surface(31, 31);
    int white[] = {0xff, 0xff, 0xff};
    int color[3];

    rect_t surf_rect = surf.get_rect();
    data[0] = 0x11;
    data[1] = surf_rect.x;
    data[2] = surf_rect.y;
    data[3] = surf_rect.width;
    data[4] = surf_rect.height;
    
    // int i;
    // for(i = 0; i < 31; i++)
    //     surf.write_pixel(i, i, white);
    for(int x = 0; x < surf_rect.width; x++)
    {
        for(int y = 0; y < surf_rect.height; y++)
        {
            surf.write_pixel(x, y, white);
        }
    }

    size_t p = 5;
    for(int x = 0; x < surf_rect.width; x++)
    {
        for(int y = 0; y < surf_rect.height; y++)
        {
            surf.read_pixel(x, y, color);
            data[p] = (color[0] + color[1] + color[2]) / 3;
            p++;
        }
    }
    net.transmit(clear, 1, target);
    net.transmit(data, (31 * 31 + 5), target);
    net.transmit(writeout, 1, target);
    // net.send
    return 0;
}