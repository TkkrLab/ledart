#include "lmcp.h"
#include <unistd.h>

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
    this->send_command(this->CLEAR, target);

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
        packet[1] = x;
        packet[2] = y;
        packet[3] = width;
        packet[4] = height;
        int surf_index;
        int count = 0;
        int ci = 0;

        // for(int line = 0, py = 0; line < size; line += width, py++)
        // {
        //     for(int px = 0; px < width); px++)
        //     {
        //         ci = surf.ctop(px, py);
        //         printf("px, py, ci: %d, %d, %d\n", px, py, ci);
        //     }
        // }
        // int px;
        // for(int line = 0, py = 0; line < size; line += width, py++)
        // {
        //     for(px = 0; px < width; px++)
        //     {
        //         // ci = surf.ctop(px, py);
        //         RGBColor_t color;
        //         surf.read_pixel(px, py, &color);
        //         packet[px + 5] = (color.red + color.green + color.blue) / 3;
        //     }
        //     packet[1] = x;
        //     packet[2] = py;
        //     packet[3] = width;
        //     packet[4] = 1;
        //     printf("py: %d\n", py);
        //     transmit(packet, width + 5, target);
        //     usleep(30000);
        //     this->send_command(this->WRITE_BUFF, target);
        // }
        
        return;
    }

}