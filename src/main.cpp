#include <stdio.h>
#include <SDL2/SDL.h>

#include <lmcp.h>
#include <surface.h>

const int MATRIX_WIDTH = 96;
const int MATRIX_HEIGHT = 48;

class Graphics: public Surface
{
public:
    Graphics(int, int);
    Graphics(int, int, int, int);
private:
};

Graphics::Graphics(int width, int height):Surface(width, height)
{
}

Graphics::Graphics(int width, int height, int x, int y):Surface(width, height, x, y)
{
}

inline void test_surface(char *target)
{
    Surface surf = Graphics(31, 31);
    int white[] = {0xff, 0xff, 0xff};

    for(int i = 0; i < 31; i++)
    {
        surf.write_pixel(i, i / 2, white);
        surf.write_pixel(i / 2, i, white);
    }

    Lmcp lmcp = Lmcp();
    lmcp.send(surf, target);
}

int main(int argc, char **argv)
{
    char target[] = "10.42.3.12";

    test_surface(target);

    return 0;
}