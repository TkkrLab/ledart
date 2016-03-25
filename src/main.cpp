#include <stdio.h>
#include <lmcp.h>
#include <surface.h>

#define MATRIX_WIDTH 96
#define MATRIX_HEIGHT 48

void test_surface(char *target)
{
    Surface surf = Surface(31, 31);
    int white[] = {0xff, 0xff, 0xff};
    int color[3];

    for(int i = 0; i < 31; i++)
    {
        surf.write_pixel(i, i/2, white);
    }

    Lmcp lmcp = Lmcp();
    lmcp.send(surf, target);
}

int main(int argc, char **argv)
{
    char target[] = "127.0.0.1";

    test_surface(target);

    return 0;
}