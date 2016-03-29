#include "lmcp.h"

void Lmcp::send_command(uint8_t command, char *target)
{
    static uint8_t data[1];

    data[0] = command;
    transmit(data, 1, target);
}

void Lmcp::send(Surface &surf, char *target)
{
    static int size;
    static int x;
    static int y;
    static int width;
    static int height;
    static int point;
    static RGBColor_t color;
    static uint8_t packet[MAX_UDP_PACKETSIZE];
    static rect_t surf_rect;

    surf_rect = surf.get_rect();
    size = surf_rect.size;
    x = surf_rect.x;
    y = surf_rect.y;
    width = surf_rect.width;
    height = surf_rect.height;

    // for debugging send clear.
    // this->send_command(this->CLEAR, target);

    if(size < (1024 - 5))
    {
        packet[0] = this->DRAW_IMG_RECT;
        packet[1] = x;
        packet[2] = y;
        packet[3] = width;
        packet[4] = height;

        point = 5;
        for(int px = 0; px < width; px++)
        {
            for(int py = 0; py < height; py++)
            {
                surf.read_pixel(py, px, &color);
                packet[point] = (color.red + color.green + color.blue) / 3;
                point++;
            }
        }
        transmit(packet, point, target);
        this->send_command(this->WRITE_BUFF, target);
    }
    else
    {
        packet[0] = this->DRAW_IMG_RECT;

        // mulpl can not ever be more then MAX_UDP_PACKETSIZE == (1019)
        int multpl = (MAX_UDP_PACKETSIZE / width);

        // we want to keep some state so px and i are declared outside of the loop.
        RGBColor_t color;
        int px, i;
        // divide and conquer. basicly chunk up the whole surface.
        for(int line = 0, py = 0; line < size; line += (width * multpl), py+=multpl)
        {
            // then for multple of lines calculate where and how to pick color from surface.
            // and where to put that in the packet.
            for(i = 0; i < multpl; i++)
            {
                // if (py + i) is bigger then the height of the matrix we break out and send what we have left.
                // since i is involved in calculating packet size we can do this.
                if((py + i) >= height)
                {
                    break;
                }
                for(px = 0; px < width; px++)
                {
                    surf.read_pixel(px, py + (i), &color);
                    packet[px + 5 + (width * i)] = (color.red + color.green + color.blue) / 3;
                    // printf("px, py, py+(i), px + 5 + (width * i): %d, %d, %d, %d\n", px, py, py + i, px + 5 + (width * i));
                }
            }

            packet[1] = x;
            packet[2] = y + py;
            packet[3] = width;
            // this works because normaly i would be 10 but when we break it it will be 8
            // and thus the packet size will work.
            packet[4] = i;

            transmit(packet, (width * i) + 5, target);
            // printf("packet size: %d\n", (width * i) + 5);
        }
        
        this->send_command(this->WRITE_BUFF, target);
        // printf("py: %d\n", py);
        return;
    }

}