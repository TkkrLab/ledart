#include <stdio.h>
#include <stdlib.h>

#include <lmcp.h>
#include <surface.h>

using namespace::std;

const int MATRIX_WIDTH = 96;
const int MATRIX_HEIGHT = 48;

class Graphics: public Surface
{
public:
    Graphics(int, int);
    Graphics(int, int, int, int);

    void xLine(int, int, int, int *);
    void yLine(int, int, int, int *);
    void draw_circle(int, int, int, int, int *);

    void draw_pixel(int, int, int *);
private:
};

Graphics::Graphics(int width, int height)
:Surface(width, height)
{
}

Graphics::Graphics(int width, int height, int x, int y)
:Surface(width, height, x, y)
{
}

void Graphics::xLine(int x1, int x2, int y, int *color)
{
    while (x1 <= x2)
    {
        Surface::write_pixel(x1, y, color);
        x1++;
    }
}

void Graphics::yLine(int x, int y1, int y2, int *color)
{
    while (y1 <= y2)
    {
        Surface::write_pixel(x, y1, color);
        y1++;
    }
}

void Graphics::draw_circle(int xc, int yc, int inner, int outer, int *color)
{
    int xo = outer;
    int xi = inner;
    int y = 0;
    int erro = 1 - xo;
    int erri = 1 - xi;

    while(xo >= y) {
        this->xLine(xc + xi, xc + xo, yc + y,  color);
        this->yLine(xc + y,  yc + xi, yc + xo, color);
        this->xLine(xc - xo, xc - xi, yc + y,  color);
        this->yLine(xc - y,  yc + xi, yc + xo, color);
        this->xLine(xc - xo, xc - xi, yc - y,  color);
        this->yLine(xc - y,  yc - xo, yc - xi, color);
        this->xLine(xc + xi, xc + xo, yc - y,  color);
        this->yLine(xc + y,  yc - xo, yc - xi, color);

        y++;

        if (erro < 0) {
            erro += 2 * y + 1;
        } else {
            xo--;
            erro += 2 * (y - xo + 1);
        }

        if (y > inner) {
            xi = y;
        } else {
            if (erri < 0) {
                erri += 2 * y + 1;
            } else {
                xi--;
                erri += 2 * (y - xi + 1);
            }
        }
    }
}

void test_surface(char *target)
{
    Graphics graphics = Graphics(31, 31);
    int white[] = {0xff, 0xff, 0xff};

    // for(int i = 0; i < 31; i++)
    // {
    //     graphics.write_pixel(i, i / 2, white);
    //     graphics.write_pixel(i / 2, i, white);
    // }

    // for(int x = 0; x < 31; x++)
    // {
    //     for(int y = 0; y < 31; y++)
    //     {
    //         graphics.write_pixel(x, y, white);
    //     }
    // }
    int radius = 10;
    graphics.draw_circle(31/2, 31/2, radius, radius, white);

    Lmcp lmcp = Lmcp();
    lmcp.send(graphics, target);
}

int main(int argc, char **argv)
{
    char target[] = "10.42.3.12";

    test_surface(target);

    return 0;
}