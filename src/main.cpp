#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <lmcp.h>
#include <graphics.h>

const int MATRIX_WIDTH = 96;
const int MATRIX_HEIGHT = 48;

Lmcp lmcp = Lmcp();
Graphics graphics = Graphics(MATRIX_WIDTH, MATRIX_HEIGHT);

void test_surface(char *target)
{
    RGBColor_t white = {0xff, 0xff, 0xff, 0};

    int radius = 10;
    graphics.draw_circle(radius, radius, 0, radius, white);

    graphics.draw_line(0, 0, MATRIX_WIDTH, MATRIX_HEIGHT, 2, white);
    // graphics.draw_rect(0, 0, MATRIX_WIDTH, MATRIX_HEIGHT, 0, white);
    int x, y, width, height;
    width = MATRIX_WIDTH / 2;
    height = MATRIX_HEIGHT / 2;
    x = (width) - (width / 2);
    y = (height) - (height / 2);
    graphics.draw_rect(x, y, 8, 8, 0, white);

    graphics.draw_rect(0, 0, MATRIX_WIDTH, MATRIX_HEIGHT, 1, white);

    graphics.draw_pixel(MATRIX_WIDTH, MATRIX_HEIGHT, white);

    lmcp.send(graphics, target);
}

int main(int argc, char **argv)
{
    // char target[] = "10.42.3.12";
    char target[] = "127.0.0.1";
    test_surface(target);

    return 0;
}