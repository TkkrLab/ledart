#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#include <GraphicsTest.h>

int main(int argc, char **argv)
{
    char target[] = "127.0.0.1";
    while(1)
    {
        test_surface(target);
        usleep(100e3);
    }
    return 0;
}