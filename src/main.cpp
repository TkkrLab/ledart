#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#include <lmcp.h>
#include <graphics.h>

const int MATRIX_WIDTH = 96;
const int MATRIX_HEIGHT = 48;

Lmcp lmcp = Lmcp();
Graphics graphics = Graphics(MATRIX_WIDTH, MATRIX_HEIGHT);

void test_surface(char *target)
{
    static int posx, posy;
    static int dirx = 1, diry = 1;
    RGBColor_t white = {0xff, 0xff, 0xff, 0};
    RGBColor_t black = {0, 0, 0, 0};

    // int radius = 10;
    // graphics.draw_circle(radius, radius, 0, radius, white);

    // graphics.draw_line(0, 0, MATRIX_WIDTH, MATRIX_HEIGHT, 2, white);
    // // graphics.draw_rect(0, 0, MATRIX_WIDTH, MATRIX_HEIGHT, 0, white);
    // int x, y, width, height;
    // width = MATRIX_WIDTH / 2;
    // height = MATRIX_HEIGHT / 2;
    // x = (width) - (width / 2);
    // y = (height) - (height / 2);
    // graphics.draw_rect(x, y, 8, 8, 0, white);

    // graphics.draw_rect(0, 0, MATRIX_WIDTH, MATRIX_HEIGHT, 1, white);

    // graphics.draw_pixel(MATRIX_WIDTH, MATRIX_HEIGHT, white);

    graphics.draw_rect(0, 0, MATRIX_WIDTH, MATRIX_HEIGHT, 0, black);

    graphics.draw_pixel(posx, posy, white);

    posx += dirx;
    if((posx >= (MATRIX_WIDTH - 1)) || (posx == 0))
    {
        dirx *= -1;
    }

    posy += diry;
    if((posy >= (MATRIX_HEIGHT - 1)) || (posy == 0))
    {
        diry *= -1;
    }

    lmcp.send(graphics, target);
}

int main(int argc, char **argv)
{
    char target[] = "10.42.3.12";
    // char target[] = "127.0.0.1";
    // char target[] = "10.42.7.124";
    while(1)
    {
        test_surface(target);
        usleep(100e3);
    }
    return 0;
}