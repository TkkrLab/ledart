#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <string.h>

#include <iostream>

#include <gflags/gflags.h>

DEFINE_double(fps, 20.0, "set fps for program to run at.");

void some_general_info()
{
    printf("Build with gcc version: %s.\n", __VERSION__);
    printf("Compiled at: %s.\n", __TIMESTAMP__);
    printf("\n");
}

int main(int argc, char **argv)
{
    ::google::ParseCommandLineFlags(&argc, &argv, true);
    std::cout << "FLAGS_fps: " << FLAGS_fps << "\n";
    some_general_info();

    return 0;
}