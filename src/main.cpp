#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

// #include <patterns.h>
// #include <BouncingDot.h>
// #include <lmcp.h>

typedef struct
{
    char file[100];
    int fps;
    bool netsilent;

} opts_t;

typedef struct
{
    char name[100];
    char option[100];
} opt_t;

opts_t opts;
opt_t named_options;

void parse_options()
{

}

int main(int argc, char **argv)
{
    some_general_info();
    // create_pattern_test();

    if(argc > 1)
    {
        printf("got arguments!: \n");
        for(int i = 1; i < argc; i++)
        {
            printf("%s \n", argv[i]);
        }
    }
    return 0;
}