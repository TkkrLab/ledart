#include <iostream>
#include <stdio.h>

using namespace std;

extern "C"
{
    #include <SDL2/SDL.h>
}

#include <eventhandler.h>
#include <patterns.h>

#include <yaml-parse.h>

// search for it with extern if you want to register a event handler.
EventHandler global_event_handler = EventHandler();

PatternJobs patternjobs = PatternJobs();

// called when keyboard intterup comes
void ki_func(int sig)
{
    printf("\nCaught keyboard interrupt.! signal: %d\n", sig);
    exit(1);
}

void arg_parse(int argc, char **argv)
{
    if(argc > 1)
    {
        for(int i = 0; i < argc; i++)
        {
            printf("arg[%d] = %s\n", i, argv[i]);
        }
    }
}

int main(int argc, char **argv)
{
    signal(SIGINT, ki_func);

    arg_parse(argc, argv);

    // parse yaml config.
    // if return less then 0 things went wrong.
    if(yaml_parse() < 0)
    {
        return -1;
    }

    for(;;)
    {
        global_event_handler.process();
        patternjobs.process();
        // SDL_Delay(30.00);
    }
    return 0;
}