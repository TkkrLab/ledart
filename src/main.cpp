#include <stdio.h>
#include <stdlib.h>

#include <lmcp.h>
#include <graphics.h>

const int MATRIX_WIDTH = 96;
const int MATRIX_HEIGHT = 48;

void test_surface(char *target)
{
    Graphics graphics = Graphics(MATRIX_WIDTH, MATRIX_HEIGHT);
    RGBColor_t white = {0xff, 0xff, 0xff, 0};

    int radius = 10;
    graphics.draw_circle(radius, radius, radius, radius, white);

    graphics.draw_line(0, 0, MATRIX_WIDTH, MATRIX_HEIGHT, 2, white);
    int x, y, width, height;
    width = MATRIX_WIDTH / 2;
    height = MATRIX_HEIGHT / 2;
    x = (width) - (width / 2);
    y = (height) - (height / 2);
    graphics.draw_rect(x, y, width, height, 2, white);

    graphics.draw_rect(0, 0, MATRIX_WIDTH, MATRIX_HEIGHT, 1, white);

    graphics.draw_pixel(MATRIX_WIDTH, MATRIX_HEIGHT, white);

    Lmcp lmcp = Lmcp();
    lmcp.send(graphics, target);
}

int main(int argc, char **argv)
{
    // char target[] = "10.42.3.12";
    char target[] = "localhost";

    test_surface(target);

    return 0;
}